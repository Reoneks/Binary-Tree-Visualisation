#include "test.h"
#include "datainput.h"
#include "binarytreefunctions.h"
#include "jsoncsvload.h"
#include "jsoncsvsave.h"
Test::Test(QString Lang){
    Language=Lang;
    input=new DataInput();
    functions=new BinaryTreeFunctions();
    functions->Language="Ua";
}
void Test::CreateFolders(){
    if(!QDir(QCoreApplication::applicationDirPath()+"\\Saves").exists()){
        QDir(QCoreApplication::applicationDirPath()).mkdir("Saves");
        QDir(QCoreApplication::applicationDirPath()+"\\Saves").mkdir("Json");
        QDir(QCoreApplication::applicationDirPath()+"\\Saves").mkdir("Csv");
    }else{
        if(!QDir(QCoreApplication::applicationDirPath()+"\\Saves\\Json").exists()){
            QDir(QCoreApplication::applicationDirPath()+"\\Saves").mkdir("Json");
        }
        if(!QDir(QCoreApplication::applicationDirPath()+"\\Saves\\Csv").exists()){
            QDir(QCoreApplication::applicationDirPath()+"\\Saves").mkdir("Csv");
        }
    }
}
bool Test::TestDataInput(QString Text){
    bool Error=false;
    QString Result;
    Result=input->TestFunction(Language);
    if(Result!="Ок"){
        QGridLayout *hlayout=new QGridLayout;
        QLabel *label = new QLabel(Text+Result);
        QWidget *mainWindow = new QWidget;
        hlayout->addWidget(label);
        mainWindow->setLayout(hlayout);
        mainWindow->setWindowTitle("Error");
        mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
        mainWindow->show();
        Error=true;
    }
    return Error;
}
bool Test::TestAddData(QString Text){
    bool Error=false;
    QString Result;
    QVector<QString> CorrectResult;
    CorrectResult<<"1"<<"3"<<"7"<<"15"<<"31"<<"Елемент 6 знаходиться глибше максимальної допустимої глибини"<<"Елемент 3 вже є в дереві"<<"Елемент 1 вже є в дереві"<<"Елемент 7 знаходиться глибше максимальної допустимої глибини";
    for(int i=0;i<input->Numbers.length();++i){
        Result=functions->AddElement(input->Numbers[i]);
        if(Result!=CorrectResult[i]){
            QGridLayout *hlayout=new QGridLayout;
            QLabel *label = new QLabel(Text+"Розбіжність правильних значень");
            QWidget *mainWindow = new QWidget;
            hlayout->addWidget(label);
            mainWindow->setLayout(hlayout);
            mainWindow->setWindowTitle("Error");
            mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
            mainWindow->show();
            Error=true;
            break;
        }
    }
    if(!Error)Result="Ок";
    return Error;
}
bool Test::TestSaveLoad(QString Text){
    bool Error=false,Error1;
    QString Result;
    QVector<int> Data;
    std::vector<std::pair<int,int>> Data1;
    Data<<1<<2<<3<<4<<5;
    QString Text1;
    for(int u=0;u<2;++u){
        int k=0;
        if(u==0)Text1="CSV";
        else if(u==1)Text1="JSON";
        JsonCsvSave *Save=new JsonCsvSave();
        Error1=Save->SaveInFile("Test",Text1,functions->head,Language);
        if(!Error1){
            JsonCsvLoad *Load=new JsonCsvLoad();
            Data1=Load->LoadFromFile("Test",Language,Text1);
        }
        if(!Error1){
            if(Data.length()==Data1.size()){
                for(int i=0;i<Data.length();++i){
                    if(Data[i]==Data1[i].first)++k;
                }
                if(k==Data.length())Result="Ок";
                else{
                    QGridLayout *hlayout=new QGridLayout;
                    QLabel *label = new QLabel(Text+"Розбіжність правильних значень");
                    QWidget *mainWindow = new QWidget;
                    hlayout->addWidget(label);
                    mainWindow->setLayout(hlayout);
                    mainWindow->setWindowTitle("Error");
                    mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
                    mainWindow->show();
                    Error=true;
                    break;
                }
            }else{
                QGridLayout *hlayout=new QGridLayout;
                QLabel *label = new QLabel(Text+"Не вдалося зчитати даних з формату "+Text1);
                QWidget *mainWindow = new QWidget;
                hlayout->addWidget(label);
                mainWindow->setLayout(hlayout);
                mainWindow->setWindowTitle("Error");
                mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
                mainWindow->show();
                Error=true;
                break;
            }
        }
    }
    QFile file;
    file.setFileName(QCoreApplication::applicationDirPath()+"\\Saves\\Csv\\Test.csv");
    file.remove();
    file.setFileName(QCoreApplication::applicationDirPath()+"\\Saves\\Json\\Test.json");
    file.remove();
    return Error;
}
bool Test::BinaryTreeFunctionsTest(QString Text){
    bool Error=false;
    int k=0;
    QString Result;
    QVector<QString> Result1;
    QVector<QString> CorrectResult;
    CorrectResult.clear();
    CorrectResult<<"1";
    k=0;
    Result1=functions->FindMinElement();
    for(int i=0;i<CorrectResult.length();++i){
        if(Result1[i]==CorrectResult[i])++k;
    }
    if(k==CorrectResult.length()){
        CorrectResult.clear();
        CorrectResult<<"1"<<"3"<<"7"<<"15"<<"31";
        k=0;
        Result1=functions->FindMaxElement();
        for(int i=0;i<CorrectResult.length();++i){
            if(Result1[i]==CorrectResult[i])++k;
        }
        if(k==CorrectResult.length()){
            k=0;
            CorrectResult.clear();
            CorrectResult<<"1"<<"3"<<"7";
            Result1=functions->FindElement(3);
            for(int i=0;i<3;++i){
                if(CorrectResult[i]==Result1[i])++k;
            }
            if(k==3){
                CorrectResult.clear();
                bool temp=false;
                Result1=functions->FindElement(7);
                if(Result1[0]=="Елемента 7 в дереві не знайдено")temp=true;
                if(temp){
                    k=0;
                    functions->CountElements(functions->head);
                    CorrectResult<<"1"<<"3"<<"7"<<"15"<<"31";
                    for(int i=0;i<CorrectResult.length();++i){
                        if(CorrectResult[i]==functions->ElementsIdForCounting[i])++k;
                    }
                    if(k==CorrectResult.length()&&functions->HowManyElements==5){
                        int n=0;
                        CorrectResult.clear();
                        k=0;
                        CorrectResult<<"1"<<"3"<<"7"<<"15";
                        n=functions->DeleteElement(4);
                        functions->CountElements(functions->head);
                        for(int i=0;i<CorrectResult.length();++i){
                            if(CorrectResult[i]==functions->ElementsIdForCounting[i])++k;
                        }
                        if(k==CorrectResult.length()&&n==31&&functions->head->Right->Right->Right->key==5){
                            functions->ClearBinaryTree();
                            Result="Ок";
                        }else{
                            QGridLayout *hlayout=new QGridLayout;
                            QLabel *label = new QLabel(Text+"Помилка видалення елемента");
                            QWidget *mainWindow = new QWidget;
                            hlayout->addWidget(label);
                            mainWindow->setLayout(hlayout);
                            mainWindow->setWindowTitle("Error");
                            mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
                            mainWindow->show();
                            Error=true;
                        }
                    }else{
                        QGridLayout *hlayout=new QGridLayout;
                        QLabel *label = new QLabel(Text+"Помилка підрахунку елементів");
                        QWidget *mainWindow = new QWidget;
                        hlayout->addWidget(label);
                        mainWindow->setLayout(hlayout);
                        mainWindow->setWindowTitle("Error");
                        mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
                        mainWindow->show();
                        Error=true;
                    }
                }else{
                    QGridLayout *hlayout=new QGridLayout;
                    QLabel *label = new QLabel(Text+"Помилка пошуку неіснуючого елемента");
                    QWidget *mainWindow = new QWidget;
                    hlayout->addWidget(label);
                    mainWindow->setLayout(hlayout);
                    mainWindow->setWindowTitle("Error");
                    mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
                    mainWindow->show();
                    Error=true;
                }
            }else{
                QGridLayout *hlayout=new QGridLayout;
                QLabel *label = new QLabel(Text+"Помилка пошуку елемента");
                QWidget *mainWindow = new QWidget;
                hlayout->addWidget(label);
                mainWindow->setLayout(hlayout);
                mainWindow->setWindowTitle("Error");
                mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
                mainWindow->show();
                Error=true;
            }
        }else{
            QGridLayout *hlayout=new QGridLayout;
            QLabel *label = new QLabel(Text+"Помилка пошуку максимального елемента");
            QWidget *mainWindow = new QWidget;
            hlayout->addWidget(label);
            mainWindow->setLayout(hlayout);
            mainWindow->setWindowTitle("Error");
            mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
            mainWindow->show();
            Error=true;
        }
    }else{
        QGridLayout *hlayout=new QGridLayout;
        QLabel *label = new QLabel(Text+"Помилка пошуку мінімального елемента");
        QWidget *mainWindow = new QWidget;
        hlayout->addWidget(label);
        mainWindow->setLayout(hlayout);
        mainWindow->setWindowTitle("Error");
        mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
        mainWindow->show();
        Error=true;
    }
    return Error;
}
