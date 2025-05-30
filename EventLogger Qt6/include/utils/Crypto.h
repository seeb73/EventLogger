#pragma once
#include <QString>

namespace Crypto {
    QString encryptAES(const QString& plainText);
    QString decryptAES(const QString& encryptedBase64);
}
