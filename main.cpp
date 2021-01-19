#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.Logo();
    if(w.BreakLogo&&w.CloseLogo)return 0;
    return a.exec();
}
