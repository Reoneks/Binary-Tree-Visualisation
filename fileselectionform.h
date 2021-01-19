#ifndef FILESELECTIONFORM_H
#define FILESELECTIONFORM_H
#include <QMainWindow>
#include <QDir>
#include <QTime>
#include <QDate>
#include <QMouseEvent>
#include <QModelIndex>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include "binarytreefunctions.h"
namespace Ui{
class FileSelectionForm;
}
class FileSelectionForm:public QMainWindow{
    Q_OBJECT
    BinaryTreeData *func;
    QString Lang;
    QString WhatToDo;
    int SaveLoadColumn,SaveLoadRow;
    QWidget *mainWindow1;
    QPushButton *Yes,*No;
    QString Format,FileForCopy;
    QMenu *File,*ChangeTheFormatUsed,*ChangeSaveOrLoadAction;
    QAction *JsonFormat,*CsvFormat,*SetActionToSave,*SetActionToLoad;
    bool DeleteStart;
    void GetFileName();
public:
    explicit FileSelectionForm(QWidget *parent = nullptr);
    std::vector<std::pair<int,int>> Data;
    bool Error;
    void GetFormat(QString WhatDo,BinaryTreeData* p,QString Language);
    ~FileSelectionForm();
protected:
    virtual bool eventFilter ( QObject * watched, QEvent * event );
private slots:
    void DeleteFile();
    void BreakDelete();
    void ChangeSaveLoad();
    void ChangeFormat();
    void on_OK_clicked();
    void on_Cancel_clicked();
    void on_Delete_clicked();
signals:
    void LoadFinished();
    void SaveFinished();
private:
    Ui::FileSelectionForm *ui;
};
#endif // FILESELECTIONFORM_H
