#pragma once
#include <QString>
#include "include/utils/ADIF.h"

class AdifFileWriter
{
public:
    AdifFileWriter(const QString& directory = ".");

    bool appendQsoToFile(const QsoData& qso);

private:
    QString directory_;
    QString makeFileName(const QsoData& qso) const;
    void ensureFileHeader(const QString& filePath);
};
