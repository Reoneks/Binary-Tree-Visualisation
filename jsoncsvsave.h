#ifndef JSONCSVSAVE_H
#define JSONCSVSAVE_H
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QFile>
#include <QGridLayout>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QTextStream>
#include "binarytreefunctions.h"
class JsonCsvSave{
    QJsonArray BinaryTree;
    QJsonObject ElementData;
    QFile file;
    QString Format;
    void GetDataFromTree(BinaryTreeData* p);
public:
    JsonCsvSave();
    bool SaveInFile(QString FileName,QString Format,BinaryTreeData *func,QString Lang);
};
#endif // JSONCSVSAVE_H
