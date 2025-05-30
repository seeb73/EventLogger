#ifndef DEBUGWINDOWDEBUGWINDOW_H
#define DEBUGWINDOWDEBUGWINDOW_H

#include <QDialog>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class DebugWindow; }
QT_END_NAMESPACE

class DebugWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DebugWindow(QWidget *parent = nullptr);
    ~DebugWindow();
public slots:
    void appendLogMessage(const QString &message); // <<< DODAJ TEN PUBLICZNY SLOT

private slots:
    void clearText();
    void copyText();
    void saveText();

private:
    Ui::DebugWindow *ui;
};

#endif // DEBUGWINDOWDEBUGWINDOW_H
