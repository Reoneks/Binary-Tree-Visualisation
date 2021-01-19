#ifndef JSONCSVLOAD_H
#define JSONCSVLOAD_H
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QLabel>
#include <QGridLayout>
#include <QCoreApplication>
#include "binarytreefunctions.h"
class JsonCsvLoad{
public:
    JsonCsvLoad();
    std::vector<std::pair<int,int>> LoadFromFile(QString FileName,QString Lang,QString Format);
};
#endif // JSONCSVLOAD_H
