#include "include/debugwindow/debugwindow.h"
#include "ui_debugwindow.h"
#include <QScrollBar>

DebugWindow::DebugWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DebugWindow)
{
    ui->setupUi(this);

    connect(ui->btnClear, &QPushButton::clicked, this, &DebugWindow::clearText);
    connect(ui->btnCopy, &QPushButton::clicked, this, &DebugWindow::copyText);
    connect(ui->btnSave, &QPushButton::clicked, this, &DebugWindow::saveText);
}

DebugWindow::~DebugWindow()
{
    delete ui;
}

void DebugWindow::clearText()
{
    ui->textEditDebug->clear();
}

void DebugWindow::copyText()
{
    ui->textEditDebug->selectAll();
    ui->textEditDebug->copy();
}

void DebugWindow::saveText()
{
    QString text = ui->textEditDebug->toPlainText();
    // Implementacja zapisu do pliku
}
// >>> UPEWNIJ SIĘ, ŻE TA METODA JEST ZAINSTALOWANA <<<
void DebugWindow::appendLogMessage(const QString &message)
{
    if (ui->textEditDebug) { // Upewnij się, że QTextEdit istnieje
        ui->textEditDebug->append(message); // Dodaj wiadomość na koniec
        // Opcjonalnie: przewiń do końca
        ui->textEditDebug->verticalScrollBar()->setValue(ui->textEditDebug->verticalScrollBar()->maximum());
    }
}
