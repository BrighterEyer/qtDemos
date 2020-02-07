#ifndef CONVERT_H
#define CONVERT_H
#include <QString>


class Convert
{

public:
    Convert();
    static QString ByteArrayToHexString(QByteArray data);
    static QByteArray HexStringToByteArray(QString HexString);

};

#endif // CONVERT_H
