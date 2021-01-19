#ifndef ENDCREDITS_H
#define ENDCREDITS_H
#include <QMainWindow>
#include <QTime>
#include <QTableWidgetItem>
#include <QPalette>
#include <QPixmap>
#include <QFontDatabase>
namespace Ui {
class EndCredits;
}
class EndCredits:public QMainWindow{
    Q_OBJECT
    QVector<QString>Data;
public:
    explicit EndCredits(QWidget *parent = nullptr,QString Language="Ua");
    void StartAnimation();
    bool Stop;
    ~EndCredits();
private:
    Ui::EndCredits *ui;
};
#endif // ENDCREDITS_H
