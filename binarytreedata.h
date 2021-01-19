#ifndef BINARYTREEDATA_H
#define BINARYTREEDATA_H
#include "binarytreeelement.h"
class BinaryTreeData:public BinaryTreeElement{
    public:
        BinaryTreeData *Left;
        BinaryTreeData *Right;
        BinaryTreeData *Parent;
        BinaryTreeData();
        virtual int getId() override;
        virtual int getKey() override;
        virtual ~BinaryTreeData() override;
};
#endif // BINARYTREEDATA_H
