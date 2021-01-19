#include "helpform.h"
#include "ui_helpform.h"
HelpForm::HelpForm(QWidget *parent):QMainWindow(parent),ui(new Ui::HelpForm){
    ui->setupUi(this);
    this->setWindowTitle("Help");
    ui->textBrowser->setReadOnly(true);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
}
void HelpForm::SetLanguage(QString Language){
    if(Language=="Ua"){
        ui->textBrowser->setHtml(QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">")+
                                 QString("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">")+
                                 QString("p, li { white-space: pre-wrap; }")+
                                 QString("</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:8.25pt; font-weight:400; font-style:normal;\">")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Довідка (F1)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - відкрити довідку.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Додати дані (I)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - відкриває форму для додавання даних в бінарне дерево. У формі є інформаційне поле і поле введення даних. При додаванні даних в дерево будуть прийняті лише цілі числа. Введення даних можна підтвердити за допомогою натискання кнопки Enter в полі введення даних.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Порахувати кількість елементів (P)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - порахувати кількість елементів в дереві. Результат буде виведений в консоль.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Видалити елемент (D)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - відкриває форму для видалення значень з дерева. Введені в форму числа будуть видалені з дерева при їх наявності. Введення даних можна підтвердити за допомогою натискання кнопки Enter в полі введення даних.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Очистити дерево (R)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - видалення всіх елементів з дерева.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Знайти елемент (F)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - відкриває форму для введення шуканого елемента. Після підтвердження числа в формі, почнеться пошук його в дереві. Введення даних можна підтвердити за допомогою натискання кнопки Enter в полі введення даних.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Знайти мінімальний елемент (N)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - пошук мінімального елемента в дереві.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Знайти максимальний елемент (M)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - пошук максимального елемента в дереві.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Зберегти дерево в файл (Ctrl-S)\\Завантажити дерево з файлу (Ctrl-L)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - спочатку відкриває форму для вибору формату файлів, а після форму для вибору імені файлу. Імена файлу вибераем подвійним натисканням. Кнопки на формі вибору імені файлу:</span></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">	1)Ок - підтвердити обране ім'я файлу</span></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">	2)Скасування - скасувати вибір імені файлу</span></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">	3)Видалити - видалити вибраний файл з диска</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Титри (T)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - відкрити форму з іменами творців проекту.</span></p></body></html>"));
    }else if(Language=="En"){
        ui->textBrowser->setHtml(QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">")+
                                 QString("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">")+
                                 QString("p, li { white-space: pre-wrap; }")+
                                 QString("</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:8.25pt; font-weight:400; font-style:normal;\">")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Help (F1)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - open help.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Add data (I)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - opens a form for adding data to a binary tree. The form has an information field and a data entry field. When adding data to the tree, only integers will be accepted. Data entry can be confirmed by pressing the Enter button in the data entry field.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Count the number of items (P)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - count the number of elements in the tree. The result will be displayed in the console.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Delete item (D)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - opens a form to remove values from a tree. The numbers entered in the form will be deleted from the tree, if any. Data entry can be confirmed by pressing the Enter button in the data entry field.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Clear tree (R)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - removal of all elements from the tree.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Find item (F)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - opens the form for entering the desired item. After confirming the number in the form, it will search for it in the tree. Data entry can be confirmed by pressing the Enter button in the data entry field.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Find min element (N)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - search for the minimum element in the tree.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Find max element (M)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - search for the maximum element in the tree.</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Save tree to file (Ctrl-S)\\Load tree from file (Ctrl-L)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - first opens a form to select a file format, and after a form to select a file name. File names are selected by double-clicking. Buttons on the file name selection form:</span></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">	1)Ok - confirm the selected file name</span></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">	2)Cancel - deselect file name</span></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">	3)Delete - delete the selected file from disk</span></p>")+
                                 QString("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>")+
                                 QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Credits (T)</span><span style=\" font-family:'MS Shell Dlg 2';\"> - open a form with the names of the creators of the project.</span></p></body></html>"));
    }
}
HelpForm::~HelpForm(){
    delete ui;
}
