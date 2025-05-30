#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
// #pragma once

#include <QObject>
#include <QSettings>
#include <QVariant>

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager(QObject *parent = nullptr);

    // QRZ credentials
    void setQrzUsername(const QString &username);
    QString getQrzUsername() const;

    void setQrzPassword(const QString &password);
    QString getQrzPassword() const;      // alias dla loadQrzPassword()
    QString loadQrzPassword() const;     // jawny AES-decode

    void saveQrzPassword(const QString &password);  // jawny AES-encode

    // Generic interface
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;
    void setValue(const QString &key, const QVariant &value);

    void saveSettings();

private:
    QString determineConfigPath();

    QString m_configFilePath;
    QSettings *m_settings;
};


#endif // SETTINGSMANAGER_H


/**
 *
 * // include/settings/SettingsManager.h
#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QVariant> // <<< DODAJ TĘ LINIĘ

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager(QObject *parent = nullptr);

    // Metody do odczytu ustawień
    QString getQrzUsername() const;
    QString getQrzPassword() const;

    // Ogólna metoda do odczytu dowolnej wartości
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const; // <<< DODAJ TĘ LINIĘ

    // Metody do zapisu ustawień
    void setQrzUsername(const QString &username);
    void setQrzPassword(const QString &password);

    // Ogólna metoda do zapisu dowolnej wartości
    void setValue(const QString &key, const QVariant &value); // <<< DODAJ TĘ LINIĘ

    void saveSettings(); // Metoda do jawnego zapisu ustawień

private:
    QSettings *m_settings; // Wskaźnik do obiektu QSettings
    QString m_configFilePath; // Ścieżka do aktywnego pliku konfiguracyjnego

    QString determineConfigPath(); // Metoda pomocnicza do określania ścieżki
};

#endif // SETTINGSMANAGER_H
**/
