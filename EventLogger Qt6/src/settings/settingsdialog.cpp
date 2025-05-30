// src/settings/settingsdialog.cpp
#include "include/settings/settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QDebug> // Dodaj dla komunikatów debugowania

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // Połącz przyciski z ui z nowymi slotami
    // Sprawdź w ui_settingsdialog.h, jak nazywają się Twoje QPushButtony.
    // Z Twojego pliku .ui wynika, że to "pushButton" i "pushButton_2"
    connect(ui->pushButton, &QPushButton::clicked, this, &SettingsDialog::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &SettingsDialog::on_pushButton_2_clicked);

    // Ustaw pole hasła jako QLineEdit::Password (ukrywa wpisywane znaki)
    ui->QRZpassword->setEchoMode(QLineEdit::Password);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

// Implementacja nowej metody ustawiającej SettingsManager
void SettingsDialog::setSettingsManager(SettingsManager *manager)
{
    m_settingsManager = manager;
    // Po ustawieniu menedżera, wczytaj istniejące ustawienia do pól GUI
    if (m_settingsManager) {
        ui->Callsign->setText(m_settingsManager->value("General/Callsign").toString());
        ui->Locator->setText(m_settingsManager->value("General/Locator").toString());
        ui->GPS_latitude->setText(m_settingsManager->value("General/GPS_latitude").toString());
        ui->GPS_longitude->setText(m_settingsManager->value("General/GPS_longitude").toString());
        ui->QRZlogin->setText(m_settingsManager->getQrzUsername());
        ui->QRZpassword->setText(m_settingsManager->getQrzPassword());
        ui->QRZapiKey->setText(m_settingsManager->value("QRZ/ApiKey").toString());
        ui->ServerAddress_1->setText(m_settingsManager->value("Server1/Address", "127.0.0.1").toString());
        ui->ServerPort_1->setText(m_settingsManager->value("Server1/Port", "2237").toString());
        ui->ServerAddress_2->setText(m_settingsManager->value("Server2/Address", "127.0.0.1").toString());
        ui->ServerPort_2->setText(m_settingsManager->value("Server2/Port", "2237").toString());

        qDebug() << "Settings loaded into dialog.";
    } else {
        qDebug() << "SettingsManager not set for SettingsDialog.";
    }
}

// Implementacja slotu dla przycisku "Zapisz"
void SettingsDialog::on_pushButton_clicked() // To odpowiada przyciskowi "Zapisz" z Twojego UI
{
    if (m_settingsManager) {
        // Zapisz wartości z pól GUI do menedżera ustawień
        m_settingsManager->setValue("General/Callsign", ui->Callsign->text());
        m_settingsManager->setValue("General/Locator", ui->Locator->text());
        m_settingsManager->setValue("General/GPS_latitude", ui->GPS_latitude->text());
        m_settingsManager->setValue("General/GPS_longitude", ui->GPS_longitude->text());
        m_settingsManager->setQrzUsername(ui->QRZlogin->text());
        m_settingsManager->setQrzPassword(ui->QRZpassword->text()); // Pamiętaj o bezpieczeństwie hasła!
        m_settingsManager->setValue("QRZ/ApiKey", ui->QRZapiKey->text());
        m_settingsManager->setValue("Server1/Address", ui->ServerAddress_1->text());
        m_settingsManager->setValue("Server1/Port", ui->ServerPort_1->text());
        m_settingsManager->setValue("Server2/Address", ui->ServerAddress_2->text());
        m_settingsManager->setValue("Server2/Port", ui->ServerPort_2->text());

        m_settingsManager->saveSettings(); // Zapisz zmiany na dysk
        qDebug() << "Settings saved from dialog.";
    }
    accept(); // Zamknij dialog po zapisaniu
}

// Implementacja slotu dla przycisku "Anuluj"
void SettingsDialog::on_pushButton_2_clicked() // To odpowiada przyciskowi "Anuluj" z Twojego UI
{
    reject(); // Zamknij dialog bez zapisywania zmian
}

/**
#include "include/settings/settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
**/