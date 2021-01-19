#include "fileselectionform.h"
#include "ui_fileselectionform.h"
#include "jsoncsvload.h"
#include "jsoncsvsave.h"
FileSelectionForm::FileSelectionForm(QWidget *parent):QMainWindow(parent),ui(new Ui::FileSelectionForm){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    Format="JSON";
    func=nullptr;
    WhatToDo="Save";
    DeleteStart=false;
    ui->SaveLoadTable->horizontalHeader()->hide();
    ui->SaveLoadTable->verticalHeader()->hide();
    ui->SaveLoadTable->horizontalHeader()->setStretchLastSection(true);
    ui->SaveLoadTable->viewport()->installEventFilter(this);
    ui->SaveLoadTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Delete->setDisabled(true);
    ui->SaveLoadTable->insertColumn(ui->SaveLoadTable->columnCount());
    File=new QMenu();
    ChangeTheFormatUsed=new QMenu();
    JsonFormat=new QAction();
    CsvFormat=new QAction();
    SetActionToSave=new QAction();
    SetActionToLoad=new QAction();
    ChangeSaveOrLoadAction=new QMenu();
    ChangeSaveOrLoadAction->addAction(SetActionToSave);
    ChangeSaveOrLoadAction->addAction(SetActionToLoad);
    ChangeTheFormatUsed->addAction(JsonFormat);
    ChangeTheFormatUsed->addAction(CsvFormat);
    File->addMenu(ChangeTheFormatUsed);
    File->addMenu(ChangeSaveOrLoadAction);
    ui->menuBar->addMenu(File);
    connect(JsonFormat,SIGNAL(triggered()),this,SLOT(ChangeFormat()),Qt::UniqueConnection);
    connect(CsvFormat,SIGNAL(triggered()),this,SLOT(ChangeFormat()),Qt::UniqueConnection);
    connect(SetActionToSave,SIGNAL(triggered()),this,SLOT(ChangeSaveLoad()),Qt::UniqueConnection);
    connect(SetActionToLoad,SIGNAL(triggered()),this,SLOT(ChangeSaveLoad()),Qt::UniqueConnection);
}
void FileSelectionForm::GetFormat(QString WhatDo,BinaryTreeData* p,QString Language){
    Lang=Language;
    WhatToDo=WhatDo;
    if(WhatToDo=="Save"){
        SetActionToSave->setDisabled(true);
        SetActionToLoad->setDisabled(false);
    }else if(WhatToDo=="Load"){
        SetActionToSave->setDisabled(false);
        SetActionToLoad->setDisabled(true);
    }
    func=p;
    Yes=nullptr;
    No=nullptr;
    QGridLayout *hlayout=new QGridLayout;
    QString Text1,Text2;
    if(Lang=="Ua"){
        if(WhatToDo=="Save"){
            Text1="Зберегти в Json";
            Text2="Зберегти в Csv";
        }else if(WhatToDo=="Load"){
            Text1="Завантажити з Json";
            Text2="Завантажити з Csv";
        }
    }else if(Lang=="En"){
        if(WhatToDo=="Save"){
            Text1="Save to Json";
            Text2="Save to Csv";
        }else if(WhatToDo=="Load"){
            Text1="Load from Json";
            Text2="Load from Csv";
        }
    }
    mainWindow1=new QWidget;
    Yes=new QPushButton(Text1);
    No=new QPushButton(Text2);
    hlayout->addWidget(Yes,0,0);
    hlayout->addWidget(No,1,0);
    connect(Yes,SIGNAL(clicked()),this,SLOT(ChangeFormat()),Qt::UniqueConnection);
    connect(No,SIGNAL(clicked()),this,SLOT(ChangeFormat()),Qt::UniqueConnection);
    mainWindow1->setLayout(hlayout);
    mainWindow1->setWindowTitle("Choose format");
    Yes->setMinimumHeight(40);
    No->setMinimumHeight(40);
    mainWindow1->setMinimumSize(250,100);
    mainWindow1->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    mainWindow1->show();
}
void FileSelectionForm::ChangeFormat(){
    auto obj=QObject::sender();
    if(obj==Yes||obj==JsonFormat){
        Format="JSON";
        JsonFormat->setDisabled(true);
        CsvFormat->setDisabled(false);
    }else if(obj==No||obj==CsvFormat){
        Format="CSV";
        JsonFormat->setDisabled(false);
        CsvFormat->setDisabled(true);
    }
    if(obj==Yes||obj==No){
        mainWindow1->close();
        disconnect(Yes,SIGNAL(clicked()),this,SLOT(ChangeFormat()));
        disconnect(No,SIGNAL(clicked()),this,SLOT(ChangeFormat()));
        Yes=nullptr;
        No=nullptr;
    }else{
        for(int i=ui->SaveLoadTable->rowCount()-1;i>-1;--i){
            ui->SaveLoadTable->removeRow(i);
        }
    }
    this->setWindowTitle(WhatToDo+" ("+Format+")");
    GetFileName();
}
void FileSelectionForm::GetFileName(){
    show();
    QString Text;
    JsonFormat->setText("Json");
    CsvFormat->setText("Csv");
    if(Lang=="Ua"){
        File->setTitle("Файл");
        SetActionToSave->setText("Зберегти");
        SetActionToLoad->setText("Завантажити");
        ChangeSaveOrLoadAction->setTitle("Змінити поточну дію");
        ChangeTheFormatUsed->setTitle("Змінити формат даних");
        ui->OK->setText("Ок");
        ui->Cancel->setText("Скасувати");
        ui->Delete->setText("Видалити");
        Text="Нове Збереження";
    }else if(Lang=="En"){
        File->setTitle("File");
        SetActionToSave->setText("Save");
        SetActionToLoad->setText("Load");
        ChangeSaveOrLoadAction->setTitle("Change current action");
        ChangeTheFormatUsed->setTitle("Change data format");
        ui->OK->setText("Ok");
        ui->Cancel->setText("Cancel");
        ui->Delete->setText("Delete");
        Text="New Save";
    }
    SaveLoadRow=0;
    SaveLoadColumn=0;
    QString rem,rem1,rem2;
    QDir dir;
    if(Format=="CSV")dir.setPath(QCoreApplication::applicationDirPath()+"\\Saves\\Csv");
    else dir.setPath(QCoreApplication::applicationDirPath()+"\\Saves\\Json");
    dir.setFilter(QDir::Files|QDir::NoSymLinks);
    QFileInfoList list=dir.entryInfoList();
    if(WhatToDo=="Save"){
        ui->SaveLoadTable->insertRow(ui->SaveLoadTable->rowCount());
        ui->SaveLoadTable->setItem(ui->SaveLoadTable->rowCount()-1,0,new QTableWidgetItem(Text));
    }else if(WhatToDo=="Load"){
        if(list.size()==0){
            QGridLayout *hlayout=new QGridLayout;
            QString Text;
            if(Lang=="Ua")Text="Збереженнь не знайдено";
            else if(Lang=="En")Text="No save found";
            QLabel *label = new QLabel(Text);
            QWidget *mainWindow = new QWidget;
            hlayout->addWidget(label);
            mainWindow->setLayout(hlayout);
            mainWindow->setWindowTitle("Error");
            mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
            mainWindow->show();
            ui->SaveLoadTable->setDisabled(true);
            ui->OK->setDisabled(true);
            ui->Delete->setDisabled(true);
        }else{
            ui->SaveLoadTable->setDisabled(false);
            ui->OK->setDisabled(false);
        }
    }
    for (int i = 0; i < list.size(); ++i){
        QFileInfo fileInfo=list.at(i);
        rem=fileInfo.fileName();
        rem2=rem.split(" ")[2];
        rem1=rem.split(" ")[1];
        rem=rem.split(" ")[0];
        ui->SaveLoadTable->insertRow(ui->SaveLoadTable->rowCount());
        QString Temp;
        if(Lang=="Ua")Temp=rem+" \n"+"Дата: "+rem1+" \n"+"Час: ";
        else if(Lang=="En")Temp=rem+" \n"+"Date: "+rem1+" \n"+"Time: ";
        if(Format=="CSV")Temp+=rem2.split(".c")[0];
        else Temp+=rem2.split(".j")[0];
        ui->SaveLoadTable->setItem(ui->SaveLoadTable->rowCount()-1,0,new QTableWidgetItem(Temp));
    }
    ui->SaveLoadTable->resizeRowsToContents();
}
bool FileSelectionForm::eventFilter(QObject *object, QEvent *event){
    if(object==ui->SaveLoadTable->viewport()){
            if(event->type() == QEvent::MouseButtonDblClick){
                QMouseEvent *ms = static_cast<QMouseEvent *>(event);
                if(ms->buttons() & Qt::LeftButton){
                    QItemSelectionModel *select=ui->SaveLoadTable->selectionModel();
                    SaveLoadRow=select->currentIndex().row();
                    SaveLoadColumn=select->currentIndex().column();
                    QModelIndex index=ui->SaveLoadTable->model()->index(SaveLoadRow, SaveLoadColumn, QModelIndex());
                    QString Temp=ui->SaveLoadTable->model()->data(index).toString();
                    if(Temp!="Нове Збереження"&&Temp!="New Save"&&!DeleteStart)ui->Delete->setDisabled(false);
                    else ui->Delete->setDisabled(true);
                }
            }
    }else if(object==mainWindow1){
        if(event->type()==QCloseEvent::Close){
            DeleteStart=false;
            ui->SaveLoadTable->setDisabled(false);
            ui->OK->setDisabled(false);
            ui->Delete->setDisabled(false);
            ui->Cancel->setDisabled(false);
            mainWindow1->removeEventFilter(this);
            disconnect(Yes,SIGNAL(clicked()),this,SLOT(DeleteFile()));
            disconnect(No,SIGNAL(clicked()),this,SLOT(BreakDelete()));
        }
    }
    return QObject::eventFilter(object, event);
}
void FileSelectionForm::on_OK_clicked(){
    QString File=ui->SaveLoadTable->takeItem(SaveLoadRow,SaveLoadColumn)->text();
    if(File=="Нове Збереження"||File=="New Save"){
        QDate dateToday=QDate::currentDate();
        QTime timeNow=QTime::currentTime();
        File="Save "+dateToday.toString("dd.MM.yyyy")+" "+timeNow.toString("hh.mm.ss");
    }else File=File.split(" ")[0]+" "+File.split(" ")[2]+" "+File.split(" ")[4];
    if(WhatToDo=="Save"){
        JsonCsvSave *Save=new JsonCsvSave();
        Error=Save->SaveInFile(File,Format,func,Lang);
        emit SaveFinished();
        close();
    }else if(WhatToDo=="Load"){
        JsonCsvLoad *Load=new JsonCsvLoad();
        Data=Load->LoadFromFile(File,Lang,Format);
        close();
        emit LoadFinished();
    }
}
void FileSelectionForm::on_Cancel_clicked(){
    close();
}
void FileSelectionForm::on_Delete_clicked(){
    ui->SaveLoadTable->setDisabled(true);
    ui->OK->setDisabled(true);
    ui->Delete->setDisabled(true);
    ui->Cancel->setDisabled(true);
    DeleteStart=true;
    QGridLayout *hlayout=new QGridLayout;
    QString Text,Text1,Text2;
    if(Lang=="Ua"){
        Text="Ви впевнені?";
        Text1="Так";
        Text2="Ні";
    }else if(Lang=="En"){
        Text="You are sure?";
        Text1="Yes";
        Text2="No";
    }
    QLabel *label = new QLabel(Text);
    mainWindow1=new QWidget;
    Yes=new QPushButton(Text1);
    No=new QPushButton(Text2);
    hlayout->addWidget(label,0,0);
    hlayout->addWidget(Yes,1,0);
    hlayout->addWidget(No,1,1);
    connect(Yes,SIGNAL(clicked()),this,SLOT(DeleteFile()),Qt::UniqueConnection);
    connect(No,SIGNAL(clicked()),this,SLOT(BreakDelete()),Qt::UniqueConnection);
    mainWindow1->setLayout(hlayout);
    mainWindow1->setWindowTitle("Delete File");
    mainWindow1->installEventFilter(this);
    mainWindow1->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    mainWindow1->show();
}
void FileSelectionForm::BreakDelete(){
    mainWindow1->close();
}
void FileSelectionForm::DeleteFile(){
    mainWindow1->close();
    QString File=ui->SaveLoadTable->takeItem(SaveLoadRow,SaveLoadColumn)->text();
    if(File!="Нове Збереження"&&File!="New Save"){
        File=File.split(" ")[0]+" "+File.split(" ")[2]+" "+File.split(" ")[4];
        QString Temp;
        if(Format=="CSV")Temp="Csv";
        else Temp="Json";
        QFile(QCoreApplication::applicationDirPath()+"\\Saves\\"+Temp+"\\"+File+"."+Temp.toLower()).remove();
        ui->SaveLoadTable->removeRow(SaveLoadRow);
        SaveLoadRow=0;
        SaveLoadColumn=0;
        ui->Delete->setDisabled(true);
        if(ui->SaveLoadTable->rowCount()==0){
            QGridLayout *hlayout=new QGridLayout;
            QString Text;
            if(Lang=="Ua")Text="Збереженнь не знайдено";
            else if(Lang=="En")Text="No save found";
            QLabel *label = new QLabel(Text);
            QWidget *mainWindow = new QWidget;
            hlayout->addWidget(label);
            mainWindow->setLayout(hlayout);
            mainWindow->setWindowTitle("Error");
            mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
            mainWindow->show();
            ui->SaveLoadTable->setDisabled(true);
            ui->OK->setDisabled(true);
            ui->Delete->setDisabled(true);
        }
    }
}
void FileSelectionForm::ChangeSaveLoad(){
    auto obj=QObject::sender();
    if(obj==SetActionToSave&&func!=nullptr){
        WhatToDo="Save";
        SetActionToSave->setDisabled(true);
        SetActionToLoad->setDisabled(false);
        ui->SaveLoadTable->setDisabled(false);
        ui->OK->setDisabled(false);
        SaveLoadRow=0;
        SaveLoadColumn=0;
    }else if(obj==SetActionToLoad){
        WhatToDo="Load";
        SetActionToSave->setDisabled(false);
        SetActionToLoad->setDisabled(true);
    }else{
        QGridLayout *hlayout=new QGridLayout;
        QString Text;
        if(Lang=="Ua")Text="Дерево порожнє";
        else if(Lang=="En")Text="Tree is empty";
        QLabel *label = new QLabel(Text);
        QWidget *mainWindow = new QWidget;
        label->setMinimumWidth(100);
        label->setMinimumHeight(40);
        hlayout->addWidget(label);
        mainWindow->setLayout(hlayout);
        mainWindow->setWindowTitle("Error");
        mainWindow1->setMinimumSize(250,100);
        mainWindow1->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
        mainWindow->show();
    }
    for(int i=ui->SaveLoadTable->rowCount()-1;i>-1;--i){
        ui->SaveLoadTable->removeRow(i);
    }
    this->setWindowTitle(WhatToDo+" ("+Format+")");
    GetFileName();
}
FileSelectionForm::~FileSelectionForm(){
    delete ui;
}
