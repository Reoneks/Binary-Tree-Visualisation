#include "jsoncsvsave.h"
JsonCsvSave::JsonCsvSave(){}
bool JsonCsvSave::SaveInFile(QString FileName,QString Format,BinaryTreeData *func,QString Lang){
    bool Error=false;
    this->Format=Format;
    if(Format=="CSV")file.setFileName(QCoreApplication::applicationDirPath()+"\\Saves\\Csv\\"+FileName+".csv");
    else file.setFileName(QCoreApplication::applicationDirPath()+"\\Saves\\Json\\"+FileName+".json");
    if(!file.open(QFile::WriteOnly)){
        QGridLayout *hlayout=new QGridLayout;
        QString Text;
        if(Lang=="Ua")Text="Неможливо створити файл";
        else if(Lang=="En")Text="Unable to create file";
        QLabel *label = new QLabel(Text);
        QWidget *mainWindow = new QWidget;
        hlayout->addWidget(label);
        mainWindow->setLayout(hlayout);
        mainWindow->setWindowTitle("Error");
        mainWindow->show();
        Error=true;
        return Error;
    }
    if(Format=="CSV"){
        GetDataFromTree(func);
    }else if(Format=="JSON"){
        QJsonObject Data;
        BinaryTree=Data["BinaryTree"].toArray();
        GetDataFromTree(func);
        Data["BinaryTree"]=BinaryTree;
        file.write(QJsonDocument(Data).toJson(QJsonDocument::Indented));
    }
    file.close();
    return Error;
}
void JsonCsvSave::GetDataFromTree(BinaryTreeData* p){
    if (p!=nullptr){
       if(Format=="CSV"){
           QTextStream InFile(&file);
           InFile<<"Element "+QString::number(p->id)+";Key: "+QString::number(p->key)+";";
           if(p->Left!=nullptr)InFile<<"LeftBranch: Element "+QString::number(p->Left->id)+";";
           else InFile<<"LeftBranch: nullptr;";
           if(p->Right!=nullptr)InFile<<"RightBranch: Element "+QString::number(p->Right->id)+";";
           else InFile<<"RightBranch: nullptr;";
           if(p->Parent!=nullptr)InFile<<"Parent: Element "+QString::number(p->Parent->id)+"\n";
           else InFile<<"Parent: nullptr\n";
       }else if(Format=="JSON"){
           ElementData["id"]="Element "+QString::number(p->id);
           ElementData["key"]=p->key;
           if(p->Left!=nullptr)ElementData["LeftBranch"]="Element "+QString::number(p->Left->id);
           else ElementData["LeftBranch"]="nullptr";
           if(p->Right!=nullptr)ElementData["RightBranch"]="Element "+QString::number(p->Right->id);
           else ElementData["RightBranch"]="nullptr";
           if(p->Parent!=nullptr)ElementData["Parent"]="Element "+QString::number(p->Parent->id);
           else ElementData["Parent"]="nullptr";
           BinaryTree.append(ElementData);
       }
       GetDataFromTree(p->Left);
       GetDataFromTree(p->Right);
    }
}
