#include "include/utils/ADIF.h"

QString makeAdifRow(const QsoData& qso)
{
    QString row;

    auto appendField = [&](const QString& name, const QString& value) {
        if (!value.isEmpty())
            row += QString("<%1:%2>%3 ").arg(name).arg(value.length()).arg(value);
    };

    appendField("QSO_DATE", qso.qsoDate);
    appendField("TIME_ON", qso.timeOn);
    appendField("CALL", qso.call);
    appendField("BAND", qso.band);
    appendField("MODE", qso.mode);
    appendField("RST_SENT", qso.rstSent);
    appendField("RST_RCVD", qso.rstRcvd);
    appendField("NAME", qso.name);
    appendField("QTH", qso.qth);

    row += "<EOR>\n";
    return row;
}
