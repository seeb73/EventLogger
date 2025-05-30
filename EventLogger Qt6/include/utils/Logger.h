#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>

class LogSignalEmitter : public QObject
{
    Q_OBJECT

public:
    static LogSignalEmitter* instance();

signals:
    void newLogMessage(const QString &message);

private:
    explicit LogSignalEmitter(QObject *parent = nullptr);
    static LogSignalEmitter* m_instance;
};

// Statyczna klasa Logger
class Logger
{
public:
    static void logDebug(const QString &msg);
    static void logInfo(const QString &msg);
    static void logWarning(const QString &msg);
    static void logError(const QString &msg);
};

// Deklaracja handlera logów Qt
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // LOGGER_H
