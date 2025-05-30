#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon> // Dodaj ten nagłówek
#include "include/debugwindow/debugwindow.h"
#include "QrzSessionManager.h"
#include "include/settings/SettingsManager.h"
#include "include/QrzSessionManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* instance();         // singleton instance getter
    QString getFreqField() const;         // returns frequency from UI


private slots:
    void openSettingsDialog();
    void openDebugWindow();
    void onFrequencyChanged(const QString &freqText);
    void onCallsignChanged(const QString &callsignText); // <<< DODAJ TĘ LINIĘ

	void onQrzLookupComplete(const QMap<QString, QString> &data);
	void onQrzLookupFailed(const QString &reason);
	void onCallsignEntered(); // Slot wywoływany, gdy użytkownik skończy wpisywać znak wywoławczy
    // void onLoginSuccess(const QString &);
    // void onLoginFailed(const QString &);
    void onCallsignFieldActivated();  // logowanie z symulacją pobrania dla uniknięcia zgubienia pierwszej łączności

private:
    void updateBandFromFrequency(const QString &freqText);
    Ui::MainWindow *ui;
    DebugWindow *m_debugWindow = nullptr; // Dodaj tę linię
    QSystemTrayIcon *m_trayIcon = nullptr; // Wskaźnik do ikony w zasobniku
	QrzSessionManager *m_qrzManager = nullptr; // Dodaj tę linię
    QrzSessionManager *sessionManager;
	SettingsManager *m_settingsManager = nullptr;
    static MainWindow* s_instance;
};

#endif // MAINWINDOW_H
