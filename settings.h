#ifndef SAVESETTINGS_H
#define SAVESETTINGS_H

# include <QJsonObject>
class Settings
{
private:
    QString color;
    int size;
public:
    Settings(QString c,int s);
    Settings(QJsonObject obj);
    QJsonObject toObject();
    int getSize();
    QString getColor();

};
#endif // SAVESETTINGS_H


