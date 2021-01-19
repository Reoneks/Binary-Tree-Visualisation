#ifndef DATAINPUT_H
#define DATAINPUT_H
#include <QMainWindow>
namespace Ui{
class DataInput;
}
class DataInput:public QMainWindow{
    Q_OBJECT
    QString Lang;
public:
    QVector<QString> Errors;
    QVector<int> Numbers;
    bool CanShow;
    QString TestFunction(QString Language);
    explicit DataInput(QWidget *parent = nullptr);
    void DataInputSetLine(QString line,QString Lang);
    ~DataInput();
protected:
    virtual bool eventFilter ( QObject * watched, QEvent * event );
private slots:
    void on_Accept_clicked();
    void on_Reject_clicked();
signals:
    void EditFinished();
private:
    Ui::DataInput *ui;
};
#endif // DATAINPUT_H
