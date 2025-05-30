#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/settings/settingsdialog.h"
#include "include/debugwindow/debugwindow.h"
#include <QIcon>
#include <QMenu>
#include <QSystemTrayIcon>
#include "include/utils/Logger.h"

MainWindow* MainWindow::s_instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_debugWindow(nullptr)
    , m_trayIcon(nullptr)
    , m_qrzManager(new QrzSessionManager(this))
    , m_settingsManager(new SettingsManager(this))

{
    s_instance = this;
    ui->setupUi(this);

    QIcon appIcon(":/icons/logo_app_50x50px.svg");
    this->setWindowIcon(appIcon);

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(appIcon);
    m_trayIcon->setToolTip("EventLogger - Program do logowania łączności w akcjach dyplomowych");
    m_trayIcon->show();

    connect(ui->actionDebug, &QAction::triggered, this, &MainWindow::openDebugWindow);

    connect(LogSignalEmitter::instance(), &LogSignalEmitter::newLogMessage,
            this, [this](const QString &message) {
        if (m_debugWindow) {
            m_debugWindow->appendLogMessage(message);
        }
    });

    connect(ui->lineCallsign, &QLineEdit::selectionChanged, this, &MainWindow::onCallsignFieldActivated);

    connect(m_qrzManager, &QrzSessionManager::lookupComplete, this, &MainWindow::onQrzLookupComplete);
    connect(m_qrzManager, &QrzSessionManager::lookupFailed, this, &MainWindow::onQrzLookupFailed);

    connect(ui->lineCallsign, &QLineEdit::editingFinished, this, &MainWindow::onCallsignEntered);

    ui->lineRSTs->setText("59");
    ui->lineRSTr->setText("59");

    QStringList modes = {"CW", "SSB", "LSB", "USB", "FM", "AM", "FT8", "FT4"};
    for (const QString &mode : modes) {
        if (ui->comboMode->findText(mode) == -1) {
            ui->comboMode->addItem(mode);
        }
    }

    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::openSettingsDialog);
    connect(ui->actionDebug, &QAction::triggered, this, &MainWindow::openDebugWindow);

    connect(ui->lineCallsign, &QLineEdit::textChanged, this, &MainWindow::onCallsignChanged);
    ui->lineCallsign->setText(ui->lineCallsign->text().toUpper());

    connect(ui->lineFreq, &QLineEdit::textChanged, this, &MainWindow::onFrequencyChanged);
    updateBandFromFrequency(ui->lineFreq->text());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSettingsDialog()
{
    SettingsDialog settingsDialog(this);
    settingsDialog.setSettingsManager(m_settingsManager);
    settingsDialog.exec();
}

void MainWindow::openDebugWindow()
{
    if (!m_debugWindow) {
        m_debugWindow = new DebugWindow(this);
    }
    m_debugWindow->show();
    m_debugWindow->activateWindow();
}

void MainWindow::onFrequencyChanged(const QString &freqText)
{
    updateBandFromFrequency(freqText);
}

void MainWindow::updateBandFromFrequency(const QString &freqText)
{
    bool ok;
    double freq = freqText.toDouble(&ok);
    QString band = "?";

    if (ok) {
        if (freq >= 1.8 && freq < 2.0) band = "160m";
        else if (freq >= 3.5 && freq < 4.0) band = "80m";
        else if (freq >= 7.0 && freq < 7.3) band = "40m";
        else if (freq >= 10.1 && freq < 10.15) band = "30m";
        else if (freq >= 14.0 && freq < 14.35) band = "20m";
        else if (freq >= 18.068 && freq < 18.168) band = "17m";
        else if (freq >= 21.0 && freq < 21.45) band = "15m";
        else if (freq >= 24.89 && freq < 24.99) band = "12m";
        else if (freq >= 28.0 && freq < 29.7) band = "10m";
        else if (freq >= 50.0 && freq < 52.0) band = "6m";
        else if (freq >= 144.0 && freq < 148.0) band = "2m";
        else if (freq >= 430.0 && freq < 440.0) band = "70cm";
    }

    ui->labelBand->setText(band);
}

void MainWindow::onCallsignChanged(const QString &callsignText)
{
    QString upperText = callsignText.toUpper();
    if (callsignText != upperText) {
        ui->lineCallsign->setText(upperText);
        ui->lineCallsign->setCursorPosition(upperText.length());
    }
}

void MainWindow::onCallsignEntered()
{
    QString callsign = ui->lineCallsign->text().trimmed();
    if (!callsign.isEmpty()) {
        // QString username = "TwojaNazwaUzytkownikaQRZ";
        // QString password = "TwojeHasloQRZ";

        QString username = m_settingsManager->getQrzUsername();
        QString password = m_settingsManager->getQrzPassword();


        ui->labelQRZStatus->setText("Status połączenia z QRZ: wyszukiwanie...");
        m_qrzManager->loginAndFetch(callsign, username, password);
    }
}

void MainWindow::onQrzLookupComplete(const QMap<QString, QString> &data)
{
    ui->labelQRZStatus->setText("Status połączenia z QRZ: połączono");
    if (data.contains("name")) {
        ui->lineName->setText(data["name"]);
    }
    if (data.contains("qth")) {
        ui->lineQTH->setText(data["qth"]);
    }
    if (data.contains("grid")) {
        ui->lineGrid->setText(data["grid"]);
    }
}

void MainWindow::onQrzLookupFailed(const QString &reason)
{
    ui->labelQRZStatus->setText("Status połączenia z QRZ: błąd - " + reason);
    qDebug() << "Błąd QRZ: " << reason;
}

void MainWindow::onCallsignFieldActivated()
{
    static bool alreadyLoggedIn = false;
    if (alreadyLoggedIn) return;

    QString username = m_settingsManager->getQrzUsername();
    QString password = m_settingsManager->getQrzPassword();

    if (!username.isEmpty() && !password.isEmpty()) {
        Logger::logInfo("[QRZ] Logowanie przy aktywacji pola Callsign...");
        m_qrzManager->loginAndFetch("SP3SEB", username, password); // Tymczasowy callsign, tylko dla sesji!
        alreadyLoggedIn = true;
    }
}

MainWindow* MainWindow::instance() {
    return s_instance;
}

QString MainWindow::getFreqField() const {
    return ui->lineFreq->text().trimmed();
}
