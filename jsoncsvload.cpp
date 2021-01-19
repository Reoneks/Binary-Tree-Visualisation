#include "jsoncsvload.h"
JsonCsvLoad::JsonCsvLoad(){}
std::vector<std::pair<int,int>> JsonCsvLoad::LoadFromFile(QString FileName,QString Lang,QString Format){
    QFile file;
    std::vector<std::pair<int,int>> Data;
    if(Format=="CSV")file.setFileName(QCoreApplication::applicationDirPath()+"\\Saves\\Csv\\"+FileName+".csv");
    else if(Format=="JSON")file.setFileName(QCoreApplication::applicationDirPath()+"\\Saves\\Json\\"+FileName+".json");
    if(!file.open(QFile::ReadOnly)){
        QGridLayout *hlayout=new QGridLayout;
        QString Text;
        if(Lang=="Ua")Text="Неможливо відкрити файл";
        else if(Lang=="En")Text="Unable to open file";
        QLabel *label = new QLabel(Text);
        QWidget *mainWindow = new QWidget;
        hlayout->addWidget(label);
        mainWindow->setLayout(hlayout);
        mainWindow->setWindowTitle("Error");
        mainWindow->show();
    }else{
        if(Format=="CSV"){
            while(!file.atEnd()){
                QString Element=file.readLine();
                Data.push_back(std::make_pair(Element.split(";")[1].split(" ")[1].toInt(),Element.split(";")[0].split(" ")[1].toInt()));
            }
        }else if(Format=="JSON"){
            QByteArray data = file.readAll();
            QJsonDocument document;
            document=document.fromJson(data);
            QJsonArray BinaryTree=document.object()["BinaryTree"].toArray();
            foreach(QJsonValue element,BinaryTree){
                QJsonObject node=element.toObject();
                Data.push_back(std::make_pair( node["key"].toInt(),node["id"].toString().split(" ")[1].toInt()));
            }
        }
        std::sort(Data.begin(),Data.end(),[](const std::pair<int,int> &left, const std::pair<int,int> &right){return left.second < right.second;});
        file.close();
    }
    return Data;
}
