#ifndef BINARYTREEELEMENT_H
#define BINARYTREEELEMENT_H
class BinaryTreeElement{
public:
    int key;
    int id;
    virtual int getKey() = 0;
    virtual int getId() = 0;
    virtual ~BinaryTreeElement() = default;
};
#endif // BINARYTREEELEMENT_H
