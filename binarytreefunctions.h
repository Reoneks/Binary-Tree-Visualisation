#ifndef BINARYTREEFUNCTIONS_H
#define BINARYTREEFUNCTIONS_H
#include "binarytreedata.h"
#include <QVector>
class BinaryTreeFunctions:public BinaryTreeData{
        int MaxDepth;
        void RestoreId(BinaryTreeData* p,BinaryTreeData *parent);
    public:
        int HowManyElements;
        QString Language;
        QVector<QString> ElementsIdForCounting;
        BinaryTreeData *head;
        BinaryTreeFunctions();
        void ClearBinaryTree();
        QVector<QString> FindElement(int element);
        QVector<QString> FindMaxElement();
        QVector<QString> FindMinElement();
        int DeleteElement(int element);
        QString AddElement(int element);
        void CountElements(BinaryTreeData* p);
        ~BinaryTreeFunctions();
};
#endif // BINARYTREEFUNCTIONS_H
