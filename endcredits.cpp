#include "endcredits.h"
#include "ui_endcredits.h"
EndCredits::EndCredits(QWidget *parent,QString Language):QMainWindow(parent),ui(new Ui::EndCredits){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    Stop=false;
    ui->Credits->horizontalHeader()->hide();
    ui->Credits->verticalHeader()->hide();
    ui->Credits->setFocusPolicy(Qt::NoFocus);
    ui->Credits->horizontalHeader()->setStretchLastSection(true);
    ui->Credits->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Credits->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Credits->setShowGrid(false);
    ui->Credits->insertColumn(ui->Credits->columnCount());
    for(int i=0;i<15;++i){
        ui->Credits->insertRow(ui->Credits->rowCount());
        Data<<"";
    }
    if(Language=="Ua")Data<<"Титри";
    else if(Language=="En")Data<<"Credits";
    Data<<"";
    Data<<"";
    Data<<"";
    Data<<"";
    if(Language=="Ua")Data<<"Розробка класів:";
    else if(Language=="En")Data<<"Class development:";
    Data<<"";
    if(Language=="Ua")Data<<"Циммерман Олексій";
    else if(Language=="En")Data<<"Zimmerman Alexey";
    Data<<"";
    Data<<"";
    if(Language=="Ua")Data<<"Файлові алгоритми і база даних:";
    else if(Language=="En")Data<<"File algorithms and database:";
    Data<<"";
    if(Language=="Ua")Data<<"Риндін Павло";
    else if(Language=="En")Data<<"Ryndin Pavel";
    Data<<"";
    Data<<"";
    if(Language=="Ua")Data<<"Дизайн:";
    else if(Language=="En")Data<<"Design:";
    Data<<"";
    if(Language=="Ua")Data<<"Породько Максим";
    else if(Language=="En")Data<<"Porodko Maksim";
    Data<<"";
    Data<<"";
    if(Language=="Ua")Data<<"Розробка алгоритмів:";
    else if(Language=="En")Data<<"Algorithm development:";
    Data<<"";
    if(Language=="Ua")Data<<"Лінець Вадим";
    else if(Language=="En")Data<<"Linets Vadim";
    for(int i=0;i<10;++i){
        Data<<"";
    }
    if(Language=="Ua")Data<<"Кінець";
    else if(Language=="En")Data<<"The end";
    for(int i=0;i<15;++i){
        Data<<"";
    }
}
void EndCredits::StartAnimation(){
    int k=400;
    int id=QFontDatabase::addApplicationFont(":/media/fonts/StarC.otf");
    for(int i=0;i<Data.length()-14;++i){
        if(Stop)return;
        int FontSize=15;
        for(int u=i;u<i+15;++u){
            if(Stop)return;
            QTableWidgetItem *item=new QTableWidgetItem("");
            QFont font;
            font.setFamily(QFontDatabase::applicationFontFamilies(id).at(0));
            font.setPixelSize(FontSize);
            item->setText(Data[u]);
            item->setFont(font);
            FontSize+=2;
            item->setTextAlignment(Qt::AlignCenter);
            ui->Credits->setItem(u-i,0,item);
        }
        ui->Credits->resizeRowsToContents();
        if(i==Data.length()-15)k+=200;
        QTime *timer = new QTime();
        timer->start();
        while(1){
            QApplication::processEvents();
            if(timer->elapsed()>=k)break;
        }
        delete timer;
    }
    close();
}
EndCredits::~EndCredits(){
    delete ui;
}
