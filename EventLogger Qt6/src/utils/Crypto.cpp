#include "include/utils/Crypto.h"
#include <QCryptographicHash>
#include <QByteArray>
#include <QVector>
#include <openssl/evp.h>
#include <openssl/rand.h>

namespace Crypto {

namespace {
QByteArray aesKey() {
    return QCryptographicHash::hash("EventLogger_AES_KEY", QCryptographicHash::Sha256);
}

QByteArray aesIv() {
    // Stały IV — opcjonalnie możesz losować i prepować
    return QByteArray(16, char(0x11));
}
}

QString encryptAES(const QString& plainText)
{
    QByteArray key = aesKey();
    QByteArray iv = aesIv();
    QByteArray input = plainText.toUtf8();

    QByteArray output;
    output.resize(input.size() + EVP_MAX_BLOCK_LENGTH);

    int outlen1 = 0, outlen2 = 0;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));
    EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(output.data()), &outlen1, reinterpret_cast<const unsigned char*>(input.data()), input.size());
    EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(output.data()) + outlen1, &outlen2);
    EVP_CIPHER_CTX_free(ctx);

    output.resize(outlen1 + outlen2);
    return output.toBase64();
}

QString decryptAES(const QString& encryptedBase64)
{
    QByteArray key = aesKey();
    QByteArray iv = aesIv();
    QByteArray input = QByteArray::fromBase64(encryptedBase64.toUtf8());

    QByteArray output;
    output.resize(input.size());

    int outlen1 = 0, outlen2 = 0;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));
    EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(output.data()), &outlen1, reinterpret_cast<const unsigned char*>(input.data()), input.size());
    EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(output.data()) + outlen1, &outlen2);
    EVP_CIPHER_CTX_free(ctx);

    output.resize(outlen1 + outlen2);
    return QString::fromUtf8(output);
}

}
