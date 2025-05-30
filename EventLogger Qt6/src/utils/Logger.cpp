#include "include/utils/Logger.h"
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

LogSignalEmitter* LogSignalEmitter::m_instance = nullptr;

LogSignalEmitter* LogSignalEmitter::instance()
{
    if (!m_instance)
        m_instance = new LogSignalEmitter();
    return m_instance;
}

LogSignalEmitter::LogSignalEmitter(QObject *parent) : QObject(parent) {}

// Statyczne metody Loggera
void Logger::logDebug(const QString &msg) { qDebug() << msg; }
void Logger::logInfo(const QString &msg) { qInfo() << msg; }
void Logger::logWarning(const QString &msg) { qWarning() << msg; }
void Logger::logError(const QString &msg) { qCritical() << msg; }

// Obsługa globalnego handlera
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString logMessage;
    QTextStream(&logMessage) << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << " ";

    switch (type) {
    case QtDebugMsg:    logMessage += "DEBUG: "; break;
    case QtInfoMsg:     logMessage += "INFO: "; break;
    case QtWarningMsg:  logMessage += "WARNING: "; break;
    case QtCriticalMsg: logMessage += "CRITICAL: "; break;
    case QtFatalMsg:    logMessage += "FATAL: "; break;
    }

    logMessage += msg;

    fprintf(stderr, "%s\n", logMessage.toLocal8Bit().constData());

    LogSignalEmitter::instance()->newLogMessage(logMessage);

    if (type == QtFatalMsg)
        abort();
}
