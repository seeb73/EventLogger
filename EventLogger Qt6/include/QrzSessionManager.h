#ifndef QRZSESSIONMANAGER_H
#define QRZSESSIONMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QRegularExpression>
#include <QMap>
#include <QUrlQuery>
#include <QTimer>

class QrzSessionManager : public QObject {
    Q_OBJECT

public:
    QrzSessionManager(QObject *parent = nullptr);
    void loginAndFetch(const QString &callsign, const QString &username, const QString &password);

signals:
    void lookupComplete(const QMap<QString, QString> &data);
    void lookupFailed(const QString &reason);

private slots:
    void onLoginFinished();
    void onLookupFinished();
    void fetchCallsignHtml();

private:
    QNetworkAccessManager *manager;
    QNetworkCookieJar *cookieJar;
    QString currentCallsign;
    QString qrzUsername;
    QString qrzPassword;

    void parseLookupHtml(const QString &html);
};

#endif // QRZSESSIONMANAGER_H
