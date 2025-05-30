#include "include/settings/SettingsManager.h"
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QStandardPaths>
#include <QFileInfo>

#include "include/utils/Crypto.h"

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
{
    m_configFilePath = determineConfigPath();
    qDebug() << "Using config file:" << m_configFilePath;

    m_settings = new QSettings(m_configFilePath, QSettings::IniFormat, this);
}

QString SettingsManager::determineConfigPath()
{
    QString configPath;

#ifdef Q_OS_LINUX
    QString systemConfigDir = "/etc/EventLogger";
    QString systemConfigFile = systemConfigDir + "/EventLogger.conf";
    if (QFile::exists(systemConfigFile)) {
        configPath = systemConfigFile;
    } else {
        qDebug() << "System-wide config not found at" << systemConfigFile << ". Checking application directory.";
        configPath = QCoreApplication::applicationDirPath() + "/EventLogger.conf";
    }
#else
    configPath = QCoreApplication::applicationDirPath() + "/EventLogger.conf";
#endif

    if (!QFile::exists(configPath)) {
        QFileInfo fileInfo(configPath);
        QString dirPath = fileInfo.absolutePath();
        if (!QFileInfo(dirPath).isDir()) {
            qWarning() << "Config directory does not exist and will not be created at runtime:" << dirPath;
        } else {
            qDebug() << "Config file does not exist, it will be created at" << configPath << "on first save.";
        }
    }

    return configPath;
}

void SettingsManager::saveQrzPassword(const QString& password)
{
    m_settings->setValue("QRZ/Password", Crypto::encryptAES(password));
}

QString SettingsManager::loadQrzPassword() const
{
    return Crypto::decryptAES(m_settings->value("QRZ/Password").toString());
}

QString SettingsManager::getQrzUsername() const
{
    return m_settings->value("QRZ/Username", "").toString();
}

void SettingsManager::setQrzUsername(const QString &username)
{
    m_settings->setValue("QRZ/Username", username);
}

void SettingsManager::setQrzPassword(const QString &password)
{
    saveQrzPassword(password);
}

QVariant SettingsManager::value(const QString &key, const QVariant &defaultValue) const
{
    return m_settings->value(key, defaultValue);
}

void SettingsManager::setValue(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

void SettingsManager::saveSettings()
{
    m_settings->sync();
    qDebug() << "Settings saved to" << m_configFilePath;
}

/**
#include "include/settings/SettingsManager.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>

#include "include/utils/Crypto.h"

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
{
    m_configFilePath = determineConfigPath();
    qDebug() << "Using config file:" << m_configFilePath;

    m_settings = new QSettings(m_configFilePath, QSettings::IniFormat, this);
}

QString SettingsManager::determineConfigPath()
{
    QString configPath;

#ifdef Q_OS_LINUX
    QString systemConfigDir = "/etc/EventLogger";
    QString systemConfigFile = systemConfigDir + "/EventLogger.conf";
    if (QFile::exists(systemConfigFile)) {
        configPath = systemConfigFile;
    } else {
        qDebug() << "System-wide config not found at" << systemConfigFile << ". Checking application directory.";
        configPath = QCoreApplication::applicationDirPath() + "/EventLogger.conf";
    }
#else
    configPath = QCoreApplication::applicationDirPath() + "/EventLogger.conf";
#endif

    if (!QFile::exists(configPath)) {
        QDir dir(QFileInfo(configPath).absolutePath());
        if (!dir.exists()) {
            if (dir.mkpath(".")) {
                qDebug() << "Created directory for config file:" << dir.absolutePath();
            } else {
                qWarning() << "Failed to create directory for config file:" << dir.absolutePath();
            }
        }
        qDebug() << "Config file does not exist, it will be created at" << configPath << "on first save.";
    }

    return configPath;
}

void SettingsManager::saveQrzPassword(const QString& password)
{
    m_settings->setValue("QRZ/Password", Crypto::encryptAES(password));
}

QString SettingsManager::loadQrzPassword() const
{
    return Crypto::decryptAES(m_settings->value("QRZ/Password").toString());
}

QString SettingsManager::getQrzUsername() const
{
    return m_settings->value("QRZ/Username", "").toString();
}

void SettingsManager::setQrzUsername(const QString &username)
{
    m_settings->setValue("QRZ/Username", username);
}

void SettingsManager::setQrzPassword(const QString &password)
{
    saveQrzPassword(password);
}

QVariant SettingsManager::value(const QString &key, const QVariant &defaultValue) const
{
    return m_settings->value(key, defaultValue);
}

void SettingsManager::setValue(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

void SettingsManager::saveSettings()
{
    m_settings->sync();
    qDebug() << "Settings saved to" << m_configFilePath;
}
**/
