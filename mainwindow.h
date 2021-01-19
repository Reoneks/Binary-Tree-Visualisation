#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QTime>
#include <QPalette>
#include <QPixmap>
#include <QMenu>
#include <QAction>
#include <QShortcut>
namespace Ui {
class MainWindow;
}
class DataInput;
class BinaryTreeFunctions;
class BinaryTreeData;
class EndCredits;
class Test;
class FileSelectionForm;
class MainWindow:public QMainWindow{
        Q_OBJECT
        QString Language;
        QVector<QAction*> LanguageList;
        QVector<QString> LanguageNames;
        BinaryTreeFunctions *functions;
        FileSelectionForm *SelectFile;
        DataInput *input;
        Test *test;
        EndCredits *Credits;
        QAction *Help,*OpenCredits,*AddDataA,*DeleteDataA,*ClearBinaryTreeA,
                *FindElementA,*FindMaxElementA,*FindMinElementA,
                *SaveTreeA,*LoadTreeA,*CountElementsA;
        QMenu *File,*Lang,*Tree;
        QShortcut *StopLogo;
        void PrintTree(BinaryTreeData* p);
        void ClearTree();
        void ConsoleLog(QString TextInConsole);
        void FindVisualization(QVector<QString> Result);
        void ClearAnimation(QVector<QLabel*>TempLabel,int time=1000);
    protected:
        virtual bool eventFilter(QObject *watched,QEvent *event);
        void closeEvent(QCloseEvent *event);
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        void Logo();
        bool BreakLogo,CloseLogo;
        ~MainWindow();
    private slots:
        void SaveLoadFile();
        void CommandDecoder();
        void AddData();
        void Find();
        void DeleteData();
        void LoadTree();
        void SaveTree();
        void OpenHelp();
        void StopTheLogo();
        void ChangeLanguage();
    private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
