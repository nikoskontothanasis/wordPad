#include "settings.h"
Settings::Settings(QString c,int s)
{
    color=c;
    size=s;
}

Settings::Settings(QJsonObject obj)
{
    color=obj["color"].toString();
    size=obj["size"].toInt();

}

QJsonObject Settings::toObject()
{
    QJsonObject x;
    x["color"]=color;
    x["size"]=size;
    return x;
}
QString Settings::getColor()
{
    return color;
}

int  Settings::getSize()
{
    return size;
}
