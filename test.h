#ifndef TEST_H
#define TEST_H
#include <QCoreApplication>
#include <QDir>
class DataInput;
class BinaryTreeFunctions;
class Test{
    QString Language;
    DataInput *input;
    BinaryTreeFunctions *functions;
public:
    Test(QString Lang);
    void CreateFolders();
    bool TestDataInput(QString Text);
    bool TestAddData(QString Text);
    bool TestSaveLoad(QString Text);
    bool BinaryTreeFunctionsTest(QString Text);
};
#endif // TEST_H
