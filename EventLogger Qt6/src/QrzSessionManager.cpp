// Zmodyfikowany QrzSessionManager z pełnymi logami
#include "include/QrzSessionManager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDebug>
#include <QNetworkCookie>
#include <QFont>
#include <QRegularExpression>
#include "include/utils/Logger.h"

QrzSessionManager::QrzSessionManager(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this)), cookieJar(new QNetworkCookieJar(this)) {
    manager->setCookieJar(cookieJar);
    cookieJar->setParent(manager);
}

void QrzSessionManager::loginAndFetch(const QString &callsign, const QString &username, const QString &password) {
    currentCallsign = callsign;
    qrzUsername = username;
    qrzPassword = password;

    Logger::logInfo("[QRZ] Rozpoczynanie logowania dla: " + qrzUsername);
    Logger::logDebug("[QRZ] Haslo: ******** (ukryto)");

    const QList<QNetworkCookie> cookies = cookieJar->cookiesForUrl(QUrl("https://www.qrz.com"));
    for (const QNetworkCookie &cookie : cookies) {
        if (cookie.name() == "xf_session" && !cookie.value().isEmpty()) {
            Logger::logDebug("[QRZ] Sesja juz istnieje, pomijam logowanie.");
            fetchCallsignHtml();
            return;
        }
    }

    QUrl loginUrl("https://www.qrz.com/login");
    QNetworkRequest request(loginUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64)");

    QUrlQuery postData;
    postData.addQueryItem("username", qrzUsername);
    postData.addQueryItem("password", qrzPassword);
    postData.addQueryItem("tquery", "Login");

    Logger::logDebug("[QRZ] Wysylam POST do: " + loginUrl.toString());
    Logger::logDebug("[QRZ] Dane POST: username=" + qrzUsername + ", password=********");

    QNetworkReply *reply = manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, this, &QrzSessionManager::onLoginFinished);
}

void QrzSessionManager::onLoginFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    const QByteArray data = reply->readAll();
    Logger::logDebug("[QRZ LOGIN] Odpowiedz HTML: \n" + QString(data));
    Logger::logDebug("[QRZ LOGIN] Status HTTP: " + QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()));
    Logger::logDebug("[QRZ LOGIN] URL odpowiedzi: " + reply->url().toString());
    Logger::logDebug("[QRZ LOGIN] Redirect: " + reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl().toString());

    const QList<QNetworkCookie> cookies = cookieJar->cookiesForUrl(QUrl("https://www.qrz.com"));
    for (const QNetworkCookie &cookie : cookies) {
        Logger::logDebug("[QRZ LOGIN] Cookie: " + QString(cookie.toRawForm()));
    }

    reply->deleteLater();

    if (data.contains("Login Successful")) {
        fetchCallsignHtml();
    } else {
        emit lookupFailed("Logowanie do QRZ.com nie powiodlo sie. Sprawdz dane logowania.");
    }
}

void QrzSessionManager::fetchCallsignHtml() {
    QUrl lookupUrl("https://www.qrz.com/lookup/" + currentCallsign);
    QNetworkRequest request(lookupUrl);
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64)");
    Logger::logInfo("[QRZ] Pobieram dane HTML dla: " + currentCallsign);
    QNetworkReply *lookupReply = manager->get(request);
    connect(lookupReply, &QNetworkReply::finished, this, &QrzSessionManager::onLookupFinished);
}

void QrzSessionManager::onLookupFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    QString html = reply->readAll();
    Logger::logDebug("[QRZ LOOKUP] HTML odpowiedzi:\n" + html.left(1000));
    reply->deleteLater();

    parseLookupHtml(html);
}

void QrzSessionManager::parseLookupHtml(const QString &html) {
    QMap<QString, QString> data;
    bool found = false;

    QRegularExpression nameRx(R"(<span[^>]*font-weight:\s*bold[^>]*>([^<]+)</span>)");
    QRegularExpression qthRx(R"(<p class=\"m0\"[^>]*>.*?<br[^>]*>([^<]+)<br/>)");
    QRegularExpression gridRx(R"(<tr><td class=\"dh\">Grid Square</td><td class=\"di\">(\w+)</td></tr>)");

    if (auto m = nameRx.match(html); m.hasMatch()) {
        data["name"] = m.captured(1);
        Logger::logDebug("[QRZ PARSER] Imie i nazwisko dopasowane: " + data["name"]);
        found = true;
    } else {
        Logger::logWarning("[QRZ PARSER] Nie dopasowano imienia i nazwiska");
    }

    if (auto m = qthRx.match(html); m.hasMatch()) {
        data["qth"] = m.captured(1);
        Logger::logDebug("[QRZ PARSER] QTH dopasowane: " + data["qth"]);
        found = true;
    } else {
        Logger::logWarning("[QRZ PARSER] Nie dopasowano QTH");
    }

    if (auto m = gridRx.match(html); m.hasMatch()) {
        data["grid"] = m.captured(1);
        Logger::logDebug("[QRZ PARSER] Grid dopasowany: " + data["grid"]);
        found = true;
    } else {
        Logger::logWarning("[QRZ PARSER] Nie dopasowano gridu");
    }

    if (found)
        emit lookupComplete(data);
    else
        emit lookupFailed("Nie znaleziono danych QRZ.com dla: " + currentCallsign);
}
