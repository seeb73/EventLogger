#pragma once
#include <QString>

struct QsoData {
    QString qsoDate;     // "YYYYMMDD"
    QString timeOn;      // "HHMM"
    QString call;
    QString band;
    QString mode;
    QString rstSent;
    QString rstRcvd;
    QString name;
    QString qth;
};

QString makeAdifRow(const QsoData& qso);
