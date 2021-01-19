#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datainput.h"
#include "endcredits.h"
#include "binarytreefunctions.h"
#include "helpform.h"
#include "test.h"
#include "fileselectionform.h"
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    LanguageNames<<"Український"<<"English";
    functions=new BinaryTreeFunctions;
    input=new DataInput();
    ClearTree();
    BreakLogo=false;
    CloseLogo=true;
    Help=new QAction();
    OpenCredits=new QAction();
    AddDataA=new QAction();
    DeleteDataA=new QAction();
    ClearBinaryTreeA=new QAction();
    FindElementA=new QAction();
    FindMaxElementA=new QAction();
    FindMinElementA=new QAction();
    SaveTreeA=new QAction();
    LoadTreeA=new QAction();
    CountElementsA=new QAction();
    File=new QMenu();
    Lang=new QMenu();
    Tree=new QMenu();
    StopLogo=new QShortcut(this);
    StopLogo->setKey(Qt::Key_Escape);
    SaveTreeA->setShortcut(Qt::CTRL + Qt::Key_S);
    LoadTreeA->setShortcut(Qt::CTRL + Qt::Key_L);
    Help->setShortcut(Qt::Key_F1);
    OpenCredits->setShortcut(Qt::Key_T);
    AddDataA->setShortcut(Qt::Key_I);
    CountElementsA->setShortcut(Qt::Key_P);
    DeleteDataA->setShortcut(Qt::Key_D);
    ClearBinaryTreeA->setShortcut(Qt::Key_R);
    FindElementA->setShortcut(Qt::Key_F);
    FindMinElementA->setShortcut(Qt::Key_N);
    FindMaxElementA->setShortcut(Qt::Key_M);
    File->addAction(Help);
    Tree->addAction(SaveTreeA);
    Tree->addAction(LoadTreeA);
    Tree->addAction(AddDataA);
    Tree->addAction(CountElementsA);
    Tree->addAction(DeleteDataA);
    Tree->addAction(ClearBinaryTreeA);
    Tree->addAction(FindElementA);
    Tree->addAction(FindMinElementA);
    Tree->addAction(FindMaxElementA);
    for(int i=0;i<LanguageNames.length();++i){
        QAction *action=new QAction;
        action->setText(LanguageNames[i]);
        LanguageList<<action;
        Lang->addAction(LanguageList[i]);
        connect(LanguageList[i],SIGNAL(triggered()),this,SLOT(ChangeLanguage()),Qt::UniqueConnection);
    }
    emit LanguageList[0]->triggered();
    LanguageList[0]->setVisible(false);
    ui->menuBar->addMenu(File);
    ui->menuBar->addMenu(Tree);
    ui->menuBar->addMenu(Lang);
    ui->menuBar->addAction(OpenCredits);
    connect(StopLogo,SIGNAL(activated()),this,SLOT(StopTheLogo()),Qt::UniqueConnection);
    connect(Help,SIGNAL(triggered()),this,SLOT(OpenHelp()),Qt::UniqueConnection);
    connect(OpenCredits,SIGNAL(triggered()),this,SLOT(CommandDecoder()),Qt::UniqueConnection);
    connect(SaveTreeA,SIGNAL(triggered()),this,SLOT(SaveLoadFile()),Qt::UniqueConnection);
    connect(LoadTreeA,SIGNAL(triggered()),this,SLOT(SaveLoadFile()),Qt::UniqueConnection);
    connect(AddDataA,SIGNAL(triggered()),this,SLOT(CommandDecoder()),Qt::UniqueConnection);
    connect(DeleteDataA,SIGNAL(triggered()),this,SLOT(CommandDecoder()),Qt::UniqueConnection);
    connect(ClearBinaryTreeA,SIGNAL(triggered()),this,SLOT(CommandDecoder()),Qt::UniqueConnection);
    connect(FindMinElementA,SIGNAL(triggered()),this,SLOT(CommandDecoder()),Qt::UniqueConnection);
    connect(FindMaxElementA,SIGNAL(triggered()),this,SLOT(CommandDecoder()),Qt::UniqueConnection);
    connect(FindElementA,SIGNAL(triggered()),this,SLOT(CommandDecoder()),Qt::UniqueConnection);
    connect(CountElementsA,SIGNAL(triggered()),this,SLOT(CommandDecoder()),Qt::UniqueConnection);
    ui->stackedWidget->setCurrentIndex(0);
    ui->ProjectName->horizontalHeader()->hide();
    ui->ProjectName->verticalHeader()->hide();
    ui->ProjectName->horizontalHeader()->setStretchLastSection(true);
    ui->ProjectName->verticalHeader()->setStretchLastSection(true);
    ui->ProjectName->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ProjectName->setFocusPolicy(Qt::NoFocus);
    ui->ProjectName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->ProjectName->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ProjectName->setShowGrid(false);
    ui->stackedWidget->installEventFilter(this);
    test=new Test(Language);
    test->CreateFolders();
}
void MainWindow::CommandDecoder(){
    auto obj=QObject::sender();
    if(obj==AddDataA){
        ui->menuBar->removeAction(ui->menuBar->actions().at(1));
        QString Text;
        if(Language=="Ua")Text="Введіть, через пробіл, числа, які хочете додати в дерево";
        else if(Language=="En")Text="Enter the numbers you want to add to the tree, separating them with a space";
        input->DataInputSetLine(Text,Language);
        input->installEventFilter(this);
        input->CanShow=true;
        input->show();
        connect(input,SIGNAL(EditFinished()),this,SLOT(AddData()),Qt::UniqueConnection);
    }else if(obj==DeleteDataA){
        ui->menuBar->removeAction(ui->menuBar->actions().at(1));
        if(functions->head!=nullptr){
            QString Text;
            if(Language=="Ua")Text="Введіть, через пробіл, числа, які хочете видалити з дерева";
            else if(Language=="En")Text="Enter the numbers you want to remove from the tree, separating them with a space";
            input->DataInputSetLine(Text,Language);
            input->installEventFilter(this);
            input->CanShow=true;
            input->show();
            connect(input,SIGNAL(EditFinished()),this,SLOT(DeleteData()),Qt::UniqueConnection);
        }else{
            if(Language=="Ua")ConsoleLog("На даний момент дерево пусте");
            else if(Language=="En")ConsoleLog("The tree is empty at the moment");
        }
    }else if(obj==ClearBinaryTreeA){
        ui->menuBar->removeAction(ui->menuBar->actions().at(1));
        functions->ClearBinaryTree();
        QVector<QLabel*>label;
        for(int i=1;i<32;++i){
            QString labelName="Element"+QString::number(i);
            QLabel *templabel=ui->centralwidget->findChild<QLabel*>(labelName);
            if(templabel!=nullptr){
                if(templabel->text()!="Null"){
                    label<<templabel;
                    templabel->setStyleSheet("QLabel{background:red;font-size:15px;border:2px solid black;border-radius:5px;}");
                }
            }
        }
        ClearAnimation(label);
        ClearTree();
        ui->menuBar->insertMenu(ui->menuBar->actions().at(1),Tree);
    }else if(obj==FindMinElementA||obj==FindMaxElementA){
        ui->menuBar->removeAction(ui->menuBar->actions().at(1));
        QVector<QString>Result;
        if(obj==FindMinElementA)Result=functions->FindMinElement();
        else if(obj==FindMaxElementA)Result=functions->FindMaxElement();
        Result<<"Find";
        FindVisualization(Result);
        ui->menuBar->insertMenu(ui->menuBar->actions().at(1),Tree);
    }else if(obj==CountElementsA){
        ui->menuBar->removeAction(ui->menuBar->actions().at(1));
        functions->CountElements(functions->head);
        QVector<QString> Result=functions->ElementsIdForCounting;
        Result<<"CountElements";
        FindVisualization(Result);
        if(Language=="Ua")ConsoleLog("Кількість елементів в дереві: "+QString::number(functions->HowManyElements));
        else if(Language=="En")ConsoleLog("Number of elements in the tree: "+QString::number(functions->HowManyElements));
        ui->menuBar->insertMenu(ui->menuBar->actions().at(1),Tree);
    }else if(obj==FindElementA){
        if(functions->head!=nullptr){
            ui->menuBar->removeAction(ui->menuBar->actions().at(1));
            QString Text;
            if(Language=="Ua")Text="Введіть число яке хочете знайти";
            else if(Language=="En")Text="Enter the number you want to find";
            input->DataInputSetLine(Text,Language);
            input->installEventFilter(this);
            input->CanShow=true;
            input->show();
            connect(input,SIGNAL(EditFinished()),this,SLOT(Find()),Qt::UniqueConnection);
        }else{
            if(Language=="Ua")ConsoleLog("На даний момент дерево пусте");
            else if(Language=="En")ConsoleLog("The tree is empty at the moment");
        }
    }else if(obj==OpenCredits){
        close();
        Credits=new EndCredits(nullptr,Language);
        Credits->installEventFilter(this);
        Credits->show();
        Credits->StartAnimation();
        show();
    }
}
void MainWindow::ClearAnimation(QVector<QLabel*>TempLabel,int time){
    QTime *timer=new QTime();
    timer->start();
    while(1){
        QApplication::processEvents();
        if(timer->elapsed()>=time){
            for(int i=0;i<TempLabel.length();++i){
                TempLabel[i]->setStyleSheet("QLabel{background:#D8D8D8;font-size:15px;border: 1px solid black;border-radius:5px;}");
            }
            break;
        }
    }
    delete timer;
}
void MainWindow::FindVisualization(QVector<QString> Result){
    if(Result.length()>1){
        bool OK;
        Result[0].toInt(&OK);
        if(!OK)ConsoleLog(Result[0]);
        else{
            for(int i=0;i<Result.length()-1;++i){
                QString labelName="Element"+Result[i];
                QVector<QLabel*>label;
                label<<ui->centralwidget->findChild<QLabel*>(labelName);
                if(label[0]!=nullptr){
                    if(i==Result.length()-2&&Result[Result.length()-1]=="Find")label[0]->setStyleSheet("QLabel{background:green;font-size:15px;border:2px solid black;border-radius:5px;}");
                    else label[0]->setStyleSheet("QLabel{background:#D8D8D8;font-size:15px;border:3px solid green;border-radius:5px;}");
                    ClearAnimation(label,700);
                }
            }
        }
    }
}
void MainWindow::Find(){
    disconnect(input,SIGNAL(EditFinished()),this,SLOT(Find()));
    QVector<int>Element;
    Element=input->Numbers;
    if(input->Errors.length()!=0){
        for(int i=0;i<input->Errors.length();++i){
            ConsoleLog(input->Errors[i]);
        }
    }
    if(Element.length()>0){
        if(Element.length()>1){
            if(Language=="Ua")ConsoleLog("Введена занадто велика кількість елементів. Буде взято тільки перший елемент.");
            else if(Language=="En")ConsoleLog("Too many items entered. Only the first element will be taken.");
        }
        QVector<QString>Result;
        Result=functions->FindElement(Element[0]);
        Result<<"Find";
        FindVisualization(Result);
    }
    ui->menuBar->insertMenu(ui->menuBar->actions().at(1),Tree);
}
void MainWindow::AddData(){
    disconnect(input,SIGNAL(EditFinished()),this,SLOT(AddData()));
    QVector<int>AddToTree;
    QVector<QLabel*>label;
    AddToTree=input->Numbers;
    if(input->Errors.length()!=0){
        for(int i=0;i<input->Errors.length();++i){
            ConsoleLog(input->Errors[i]);
        }
    }
    if(AddToTree.length()>0){
        QString Result;
        int k=0;
        for(int i=0;i<AddToTree.length();++i){
            Result=functions->AddElement(AddToTree[i]);
            bool OK;
            Result.toInt(&OK);
            if(!OK)ConsoleLog(Result);
            else{
                QString labelName="Element"+Result;
                label<<ui->centralwidget->findChild<QLabel*>(labelName);
                if(label[k]!=nullptr){
                    label[k]->setStyleSheet("QLabel{background:green;}");
                }
                ++k;
            }
        }
        PrintTree(functions->head);
        ClearAnimation(label);
    }
    ui->menuBar->insertMenu(ui->menuBar->actions().at(1),Tree);
}
void MainWindow::DeleteData(){
    disconnect(input,SIGNAL(EditFinished()),this,SLOT(DeleteData()));
    QVector<int>DeleteFromTree;
    DeleteFromTree=input->Numbers;
    if(input->Errors.length()!=0){
        for(int i=0;i<input->Errors.length();++i){
            ConsoleLog(input->Errors[i]);
        }
    }
    if(DeleteFromTree.length()>0){
        for(int i=0;i<DeleteFromTree.length();++i){
            QVector<QString>Result;
            Result=functions->FindElement(DeleteFromTree[i]);
            bool OK;
            Result[0].toInt(&OK);
            if(!OK)ConsoleLog(Result[0]);
            else{
                int Number;
                QVector<QLabel*>label;
                Number=functions->DeleteElement(DeleteFromTree[i]);
                QString labelName="Element"+Result[Result.length()-1],labelName1;
                if(Number!=0)labelName1="Element"+QString::number(Number);
                label<<ui->centralwidget->findChild<QLabel*>(labelName);
                if(Number!=0)label<<ui->centralwidget->findChild<QLabel*>(labelName1);
                if(label[0]!=nullptr){
                    label[0]->setStyleSheet("QLabel{background:red;font-size:15px;border:2px solid black;border-radius:5px;}");
                }
                if(Number!=0){
                    if(label[1]!=nullptr){
                        label[1]->setStyleSheet("QLabel{background:#D8D8D8;font-size:15px;border:3px solid black;border-radius:5px;}");
                    }
                }
                ClearAnimation(label);
                ClearTree();
                PrintTree(functions->head);
            }
        }
    }
    ui->menuBar->insertMenu(ui->menuBar->actions().at(1),Tree);
}
void MainWindow::PrintTree(BinaryTreeData* p){
    if (p!=nullptr){
        QString labelName="Element"+QString::number(p->id);
        QLabel *label=ui->centralwidget->findChild<QLabel*>(labelName);
        if(label!=nullptr){
            label->setText(QString::number(p->key));
            if(label->styleSheet()!="QLabel{background:green;}")label->setStyleSheet("QLabel{background:#D8D8D8;font-size:15px;border:1px solid black;border-radius:5px;}");
            else label->setStyleSheet("QLabel{background:green;font-size:15px;border:1px solid black;border-radius:5px;}");
        }
        this->PrintTree(p->Left);
        this->PrintTree(p->Right);
    }
}
void MainWindow::ClearTree(){
    for(int i=1;i<32;++i){
        QString labelName="Element"+QString::number(i);
        QLabel *label=ui->centralwidget->findChild<QLabel*>(labelName);
        if(label!=nullptr){
            label->setText("Null");
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet("QLabel{border:1px solid black;font-size:15px;border-radius:5px;background:#A4A4A4}");
        }
    }
}
void MainWindow::SaveLoadFile(){
    auto obj=QObject::sender();
    QString SaveOrLoad="Save";
    if(obj==SaveTreeA)SaveOrLoad="Save";
    else if(obj==LoadTreeA)SaveOrLoad="Load";
    SelectFile=new FileSelectionForm();
    bool Ok=true;
    if(SaveOrLoad=="Save"&&functions->head==nullptr)Ok=false;
    if(Ok){
        SelectFile->GetFormat(SaveOrLoad,functions->head,Language);
        connect(SelectFile,SIGNAL(SaveFinished()),this,SLOT(SaveTree()),Qt::UniqueConnection);
        connect(SelectFile,SIGNAL(LoadFinished()),this,SLOT(LoadTree()),Qt::UniqueConnection);
    }
    else{
        if(Language=="Ua")ConsoleLog("На даний момент дерево пусте");
        else if(Language=="En")ConsoleLog("The tree is empty at the moment");
    }
}
void MainWindow::LoadTree(){
    disconnect(SelectFile,SIGNAL(LoadFinished()),this,SLOT(LoadTree()));
    ui->menuBar->removeAction(ui->menuBar->actions().at(1));
    std::vector<std::pair<int,int>> Data=SelectFile->Data;
    if(Data.size()>0){
        QVector<QLabel*>label;
        functions->ClearBinaryTree();
        ClearTree();
        QString Result;
        int k=0;
        if(Language=="Ua")ConsoleLog("Успішно завантажено!");
        else if(Language=="En")ConsoleLog("Successfully loaded!");
        for(unsigned long long i=0;i<Data.size();++i){
            Result=functions->AddElement(int(Data[i].first));
            bool OK;
            Result.toInt(&OK);
            if(!OK)ConsoleLog(Result);
            else{
                QString labelName="Element"+Result;
                label<<ui->centralwidget->findChild<QLabel*>(labelName);
                if(label[k]!=nullptr){
                    label[k]->setStyleSheet("QLabel{background:green;}");
                }
                ++k;
            }
        }
        PrintTree(functions->head);
        ClearAnimation(label);
    }
    ui->menuBar->insertMenu(ui->menuBar->actions().at(1),Tree);
}
void MainWindow::OpenHelp(){
    HelpForm *helpform=new HelpForm();
    helpform->SetLanguage(Language);
    helpform->show();
}
void MainWindow::ChangeLanguage(){
    auto obj=QObject::sender();
    if(obj==LanguageList[0]){
        Language="Ua";
        AddDataA->setText("Додати дані");
        ClearBinaryTreeA->setText("Очистити дерево");
        FindMinElementA->setText("Знайти мінімальний елемент");
        FindMaxElementA->setText("Знайти максимальний елемент");
        DeleteDataA->setText("Видалити елемент");
        CountElementsA->setText("Порахувати кількість елементів");
        FindElementA->setText("Знайти елемент");
        LoadTreeA->setText("Завантажити дерево з файлу");
        SaveTreeA->setText("Зберегти дерево в файл");
        Help->setText("Довідка");
        File->setTitle("Файл");
        Lang->setTitle("Мова");
        Tree->setTitle("Дерево");
        OpenCredits->setText("Титри");
        ui->Console->clear();
    }else if(obj==LanguageList[1]){
        Language="En";
        AddDataA->setText("Add data");
        ClearBinaryTreeA->setText("Clear binary tree");
        FindMinElementA->setText("Find min element");
        FindMaxElementA->setText("Find max element");
        DeleteDataA->setText("Delete element");
        CountElementsA->setText("Count elements");
        FindElementA->setText("Find element");
        LoadTreeA->setText("Load tree");
        SaveTreeA->setText("Save tree");
        Help->setText("Help");
        File->setTitle("File");
        Lang->setTitle("Language");
        Tree->setTitle("Tree");
        OpenCredits->setText("Credits");
        ui->Console->clear();
    }
    for(int i=0;i<LanguageList.length();++i){
        if(obj==LanguageList[i])LanguageList[i]->setVisible(false);
        else LanguageList[i]->setVisible(true);
    }
    functions->Language=Language;
    this->setWindowTitle("Binary Tree ("+Language+")");
}
void MainWindow::ConsoleLog(QString TextInConsole){
    ui->Console->append(TextInConsole+"\n");
}
void MainWindow::Logo(){
    QPalette pal;
    QPixmap map;
    map.load(":/media/images/MainwindowBackground.png");
    map=map.scaled(1391,421,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    ui->menuBar->setVisible(false);
    QVector<QLabel*>label;
    ui->progressBar->setVisible(false);
    ui->label->setVisible(false);
    ui->progressBar->setValue(0);
    QVector<QString> LoadText;
    QVector<int> LoadNumber;
    LoadText<<"Завантаження фонових зображень"<<"Перевірка наявності каталогів данних"<<"Завантаження мовних пакетів"<<"Тестування форми введення: "<<"Тестування функції додавання елементів: "<<"Тестування системи збережень і завантаження: "<<"Тестування інших функцій для роботи з деревом: ";
    LoadNumber<<10<<10<<20<<15<<10<<15<<20;
    QString ProjectNameText="Binary Tree Project";
    ui->ProjectName->insertRow(ui->ProjectName->rowCount());
    ui->ProjectName->setStyleSheet("QTableWidget{background-color:transparent;border:transparent}");
    ClearAnimation(label,500);
    for(int i=0;i<ProjectNameText.length();++i){
        if(BreakLogo)return;
        ui->ProjectName->insertColumn(ui->ProjectName->columnCount());
        QTableWidgetItem *item=new QTableWidgetItem("");
        QFont font;
        font.setWeight(90);
        font.setPixelSize(30);
        item->setText(ProjectNameText.at(i));
        item->setFont(font);
        ui->ProjectName->setItem(0,ui->ProjectName->columnCount()-1,item);
        ui->ProjectName->resizeColumnsToContents();
        ClearAnimation(label,200);
    }
    ClearAnimation(label,500);
    ui->progressBar->setVisible(true);
    ui->label->setVisible(true);
    ui->ProjectLogo->setVisible(false);
    ui->ProjectName->setVisible(false);
    qsrand(uint(time(nullptr)));
    int Progress=0;
    ui->progressBar->setAlignment(Qt::AlignCenter);
    QFont font,font1;
    font.setWeight(80);
    ui->progressBar->setFont(font);
    font1.setPixelSize(14);
    font1.setWeight(65);
    ui->label->setFont(font1);
    ui->label->setAlignment(Qt::AlignCenter);
    QString Result="OK";
    bool Error=false;
    for(int i=0;i<LoadText.length();++i){
        if(BreakLogo)return;
        if(i<3)ui->label->setText(LoadText[i]);
        else ui->label->setText(LoadText[i]+"...");
        if(i==3)Error=test->TestDataInput(LoadText[i]);
        else if(i==4)Error=test->TestAddData(LoadText[i]);
        else if(i==5)Error=test->TestSaveLoad(LoadText[i]);
        else if(i==6)Error=test->BinaryTreeFunctionsTest(LoadText[i]);
        if(Error)break;
        for(;LoadNumber[i]>0;){
            if(BreakLogo)return;
            int u=qrand()%LoadNumber[i]+1;
            Progress+=u;
            LoadNumber[i]-=u;
            ui->progressBar->setValue(Progress);
            ClearAnimation(label,300);
        }
        if(i>=3){
            ui->label->setText(LoadText[i]+Result);
            ClearAnimation(label,300);
            if(Progress==100){
                ui->label->setText("Готово");
                ClearAnimation(label,200);
            }
        }
    }
    BreakLogo=true;
    CloseLogo=false;
    disconnect(StopLogo,SIGNAL(activated()),this,SLOT(StopTheLogo()));
    if(!Error){
        ClearAnimation(label,600);
        map=map.scaled(1391,410,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
        ui->centralwidget->setPalette(pal);
        ui->centralwidget->setAutoFillBackground(true);
        ui->stackedWidget->setCurrentIndex(1);
        ui->menuBar->setVisible(true);
    }else{
        close();
    }
}
void MainWindow::SaveTree(){
    disconnect(SelectFile,SIGNAL(SaveFinished()),this,SLOT(SaveTree()));
    if(!SelectFile->Error){
        if(Language=="Ua")ConsoleLog("Успішно збережено!");
        else if(Language=="En")ConsoleLog("Successfully saved!");
    }
}
bool MainWindow::eventFilter(QObject *object, QEvent *event){
    if(object==input){
        if(event->type()==QCloseEvent::Close&&input->CanShow){
            ui->menuBar->insertMenu(ui->menuBar->actions().at(1),Tree);
        }
    }else if(object==Credits){
        if(event->type()==QCloseEvent::Close){
            Credits->close();
            show();
            Credits->Stop=true;
        }
    }
    return QObject::eventFilter(object, event);
}
void MainWindow::closeEvent(QCloseEvent *event){
    if(!BreakLogo){
        BreakLogo=true;
    }
    event->accept();
}
void MainWindow::StopTheLogo(){
    disconnect(StopLogo,SIGNAL(activated()),this,SLOT(StopTheLogo()));
    CloseLogo=false;
    BreakLogo=true;
    QPalette pal;
    QPixmap map;
    map.load(":/media/images/MainwindowBackground.png");
    map=map.scaled(1391,410,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    ui->stackedWidget->setCurrentIndex(1);
    ui->menuBar->setVisible(true);
}
MainWindow::~MainWindow(){
    disconnect(SaveTreeA,SIGNAL(triggered()),this,SLOT(SaveLoadFile()));
    disconnect(LoadTreeA,SIGNAL(triggered()),this,SLOT(SaveLoadFile()));
    disconnect(Help,SIGNAL(triggered()),this,SLOT(OpenHelp()));
    disconnect(AddDataA,SIGNAL(triggered()),this,SLOT(CommandDecoder()));
    disconnect(CountElementsA,SIGNAL(triggered()),this,SLOT(CommandDecoder()));
    disconnect(DeleteDataA,SIGNAL(triggered()),this,SLOT(CommandDecoder()));
    disconnect(ClearBinaryTreeA,SIGNAL(triggered()),this,SLOT(CommandDecoder()));
    disconnect(FindElementA,SIGNAL(triggered()),this,SLOT(CommandDecoder()));
    disconnect(FindMinElementA,SIGNAL(triggered()),this,SLOT(CommandDecoder()));
    disconnect(FindMaxElementA,SIGNAL(triggered()),this,SLOT(CommandDecoder()));
    disconnect(OpenCredits,SIGNAL(triggered()),this,SLOT(CommandDecoder()));
    for(int i=LanguageList.length()-1;i>=0;--i){
        delete LanguageList[i];
    }
    delete Help;
    delete OpenCredits;
    delete SaveTreeA;
    delete LoadTreeA;
    delete AddDataA;
    delete CountElementsA;
    delete DeleteDataA;
    delete ClearBinaryTreeA;
    delete FindElementA;
    delete FindMinElementA;
    delete FindMaxElementA;
    delete File;
    delete Lang;
    delete Tree;
    delete functions;
    delete input;
    delete ui;
}
