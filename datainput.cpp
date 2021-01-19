#include "datainput.h"
#include "ui_datainput.h"
DataInput::DataInput(QWidget *parent):QMainWindow(parent),ui(new Ui::DataInput){
    ui->setupUi(this);
    ui->InformationLine->setReadOnly(true);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    CanShow=true;
    QFont font;
    font.setPixelSize(15);
    ui->InformationLine->setStyleSheet("#InformationLine{border:none; outline: none;}");
    ui->InformationLine->setFont(font);
    ui->DataInputLine->installEventFilter(this);
}
QString DataInput::TestFunction(QString Language){
    Lang=Language;
    ui->DataInputLine->setText("1 qw2 2 2s 3 ef 4 http 5 6 alfa 3 1 7");
    emit ui->Accept->clicked();
    QVector<int> CorrectResultNumbers;
    int k=0;
    CorrectResultNumbers<<1<<2<<3<<4<<5<<6<<3<<1<<7;
    if(CorrectResultNumbers.length()==Numbers.length()){
        for(int i=0;i<Numbers.length();++i){
            if(Numbers[i]==CorrectResultNumbers[i])++k;
        }
    }else return "Помилка зчитування вхідних чисел";
    if(k==Numbers.length()){
        QVector<QString> CorrectErrors;
        CorrectErrors<<"Введене значення \'qw2\' не є цілочисельним. Воно не буде додано в дерево.";
        CorrectErrors<<"Введене значення \'2s\' не є цілочисельним. Воно не буде додано в дерево.";
        CorrectErrors<<"Введене значення \'ef\' не є цілочисельним. Воно не буде додано в дерево.";
        CorrectErrors<<"Введене значення \'http\' не є цілочисельним. Воно не буде додано в дерево.";
        CorrectErrors<<"Введене значення \'alfa\' не є цілочисельним. Воно не буде додано в дерево.";
        if(CorrectErrors.length()==Errors.length()){
            k=0;
            for(int i=0;i<Errors.length();++i){
                if(CorrectErrors[i]==Errors[i])++k;
            }
            if(k==Errors.length())return "Ок";
            else return "Розбіжність помилкових значень";
        }else return "Помилка зчитування вхідних помилкових значень";
    }else return "Розбіжність правильних значень";
}
void DataInput::DataInputSetLine(QString line,QString Language){
    ui->InformationLine->setPlainText(line);
    if(Language=="Ua"){
        ui->Accept->setText("Ок");
        ui->Reject->setText("Скасувати");
    }else if(Language=="En"){
        ui->Accept->setText("Ok");
        ui->Reject->setText("Cancel");
    }
    Lang=Language;
}
DataInput::~DataInput(){
    delete ui;
}
void DataInput::on_Accept_clicked(){
    Numbers.clear();
    Errors.clear();
    bool Ok;
    QStringList List=ui->DataInputLine->text().split(" ");
    for(int i=0;i<List.length();++i){
        List.at(i).toInt(&Ok);
        if(Ok)Numbers.append(List.at(i).toInt());
        else{
            if(Lang=="Ua")Errors<<"Введене значення \'"+List.at(i)+"\' не є цілочисельним. Воно не буде додано в дерево.";
            else if(Lang=="En")Errors<<"The entered value \'"+List.at(i)+"\' is not integer. It will not be added to the tree.";
        }
    }
    ui->DataInputLine->clear();
    CanShow=false;
    close();
    emit EditFinished();
}
void DataInput::on_Reject_clicked(){
    Numbers.clear();
    Errors.clear();
    ui->DataInputLine->clear();
    CanShow=false;
    close();
    emit EditFinished();
}
bool DataInput::eventFilter(QObject *object, QEvent *event){
    if(object==ui->DataInputLine&&event->type() == QEvent::KeyPress){
        QKeyEvent *e = static_cast<QKeyEvent*>(event);
        if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter){
            on_Accept_clicked();
        }
    }
    return QObject::eventFilter(object, event);
}
