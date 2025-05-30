#ifndef SETTINGSSETTINGSDIALOG_H
#define SETTINGSSETTINGSDIALOG_H

#include <QDialog>
#include "SettingsManager.h" // <<< DODAJ TĘ LINIĘ

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsDialog; }
QT_END_NAMESPACE

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
	~SettingsDialog();

	// Nowa metoda do ustawiania menedżera ustawień
	void setSettingsManager(SettingsManager *manager);
private slots:
	// Slot dla przycisku "Zapisz" (lub OK z QDialogButtonBox)
	void on_pushButton_clicked(); // <<< ZMIENIONO DLA Twojego QPushButton "Zapisz"
	// Slot dla przycisku "Anuluj"
	void on_pushButton_2_clicked(); // <<< DODANO DLA Twojego QPushButton "Anuluj"

private:
    Ui::SettingsDialog *ui;
	SettingsManager *m_settingsManager = nullptr; // <<< DODAJ TĘ LINIĘ
};

#endif // SETTINGSSETTINGSDIALOG_H
