#include "binarytreefunctions.h"
BinaryTreeFunctions::BinaryTreeFunctions(){
    head=nullptr;
    MaxDepth=5;
    HowManyElements=0;
}
void BinaryTreeFunctions::ClearBinaryTree(){
    head=nullptr;
}
QVector<QString> BinaryTreeFunctions::FindElement(int element){
    int Return=-999;
    QVector<QString>Result;
    BinaryTreeData *temp=head;
    while(true){
        if(temp->key==element){
            Result<<QString::number(temp->id);
            Return=element;
            break;
        }
        if(temp->Left==nullptr&&temp->Right==nullptr)break;
        else if(element<temp->key&&temp->Left!=nullptr){Result<<QString::number(temp->id);temp=temp->Left;}
        else if(element<temp->key&&temp->Left==nullptr)break;
        else if(element>temp->key&&temp->Right==nullptr)break;
        else{Result<<QString::number(temp->id);temp=temp->Right;}
    }
    if(Return==-999){
        Result.clear();
        if(Language=="Ua")Result<<"Елемента "+QString::number(element)+" в дереві не знайдено";
        else if(Language=="En")Result<<"Element "+QString::number(element)+" not found in tree";
    }
    return Result;
}
QVector<QString> BinaryTreeFunctions::FindMaxElement(){
    QVector<QString>Result;
    if(head!=nullptr){
        BinaryTreeData *temp=head;
        while(true){
            if(temp->Right==nullptr){
                Result<<QString::number(temp->id);
                return Result;
            }
            Result<<QString::number(temp->id);
            temp=temp->Right;
        }
    }else{
        if(Language=="Ua")Result<<"На даний момент дерево пусте";
        else if(Language=="En")Result<<"The tree is empty at the moment";
    }
    return Result;
}
QVector<QString> BinaryTreeFunctions::FindMinElement(){
    QVector<QString>Result;
    if(head!=nullptr){
        BinaryTreeData *temp=head;
        while(true){
            if(temp->Left==nullptr){
                Result<<QString::number(temp->id);
                return Result;
            }
            Result<<QString::number(temp->id);
            temp=temp->Left;
        }
    }else{
        if(Language=="Ua")Result<<"На даний момент дерево пусте";
        else if(Language=="En")Result<<"The tree is empty at the moment";
    }
    return Result;
}
int BinaryTreeFunctions::DeleteElement(int element){
       int Result=0;
       BinaryTreeData *curr;
       curr=head;
       while(curr!=nullptr){
          if(curr->key==element){
             break;
          }else{
             if(element>curr->key)curr=curr->Right;
             else curr=curr->Left;
          }
       }
       if(curr->Left==nullptr&&curr->Right==nullptr){
          if(curr==head)head=nullptr;
          else{
              if(curr->Parent->Left==curr)curr->Parent->Left=nullptr;
              else curr->Parent->Right=nullptr;
              delete curr;
          }
       }else if((curr->Left==nullptr&&curr->Right!=nullptr)||(curr->Left!=nullptr&&curr->Right==nullptr)){
          if(curr->Left==nullptr){
             Result=curr->Right->id;
             if(curr==head){
                 head=curr->Right;
                 RestoreId(head,nullptr);
             }else{
                 if(curr->Parent->Left==curr){
                    curr->Parent->Left=curr->Right;
                    RestoreId(curr->Right,curr->Parent);
                    delete curr;
                 }else{
                    curr->Parent->Right=curr->Right;
                    RestoreId(curr->Right,curr->Parent);
                    delete curr;
                 }
             }
          }else{
              Result=curr->Left->id;
              if(curr==head){
                  head=curr->Left;
                  RestoreId(head,nullptr);
              }else{
                  if(curr->Parent->Left==curr){
                     curr->Parent->Left=curr->Left;
                     RestoreId(curr->Left,curr->Parent);
                     delete curr;
                  }else{
                     curr->Parent->Right=curr->Left;
                     RestoreId(curr->Left,curr->Parent);
                     delete curr;
                  }
              }
          }
       }else if(curr->Left!=nullptr&&curr->Right!=nullptr){
         if(curr==head){
             BinaryTreeData *temp=head->Right;
             while(temp->Left!=nullptr){
                 temp=temp->Left;
             }
             Result=temp->id;
             if(temp->Parent!=head){
                 if(temp->Right==nullptr)temp->Parent->Left=nullptr;
                 else temp->Parent->Left=temp->Right;
                 temp->Right=head->Right;
                 temp->Left=head->Left;
                 head=temp;
             }else{
                 temp->Left=head->Left;
                 head=temp;
             }
             RestoreId(head,nullptr);
         }else{
             BinaryTreeData *chkr;
             chkr=curr->Right;
             if((chkr->Left==nullptr)&&(chkr->Right==nullptr)){
               Result=chkr->id;
               chkr->Left=curr->Left;
               if(curr==curr->Parent->Left)curr->Parent->Left=chkr;
               else curr->Parent->Right=chkr;
               RestoreId(chkr,curr->Parent);
             }else{
               if((curr->Right)->Left!=nullptr){
                  BinaryTreeData *lcurr;
                  BinaryTreeData *lcurrp;
                  lcurrp=curr->Right;
                  lcurr=curr->Right->Left;
                  while(lcurr->Left!=nullptr){
                     lcurrp=lcurr;
                     lcurr=lcurr->Left;
                  }
                  Result=lcurr->id;
                  if(lcurr->Right==nullptr)lcurrp->Left=nullptr;
                  else lcurrp->Left=lcurr->Right;
                  curr->key=lcurr->key;
                  delete lcurr;
                  RestoreId(curr,curr->Parent);
               }else{
                  Result=curr->Right->id;
                  curr->key=curr->Right->key;
                  curr->Right=curr->Right->Right;
                  RestoreId(curr,curr->Parent);
               }
            }
         }
     }
     return Result;
}
QString BinaryTreeFunctions::AddElement(int element){
    BinaryTreeData *temp=new BinaryTreeData;
    QString Return;
    temp->key=element;
    temp->Left=nullptr;
    temp->Right=nullptr;
    if(!head){
        Return=QString::number(1);
        temp->id=1;
        temp->Parent=nullptr;
        head=temp;
    }else{
        BinaryTreeData *ElementNow=head;
        int depth=0;
        for(;;){
            if(ElementNow->key!=element){
                ++depth;
                if(ElementNow->Left!=nullptr&&ElementNow->key>element){
                    ElementNow=ElementNow->Left;
                }else if(ElementNow->Right!=nullptr&&ElementNow->key<element){
                    ElementNow=ElementNow->Right;
                }else{
                    if(ElementNow->key>element)temp->id=ElementNow->id*2;
                    else if(ElementNow->key<element)temp->id=ElementNow->id*2+1;
                    if(depth<MaxDepth){
                        Return=QString::number(temp->id);
                        if(ElementNow->key>element)ElementNow->Left=temp;
                        else if(ElementNow->key<element)ElementNow->Right=temp;
                        temp->Parent=ElementNow;
                    }else{
                        if(Language=="Ua")return "Елемент "+QString::number(element)+" знаходиться глибше максимальної допустимої глибини";
                        else if(Language=="En")return "Element "+QString::number(element)+" is deeper than the maximum allowable depth";
                    }
                    break;
               }
            }else{
                if(Language=="Ua")return "Елемент "+QString::number(element)+" вже є в дереві";
                else if(Language=="En")return "Element "+QString::number(element)+" already in the tree";
            }
        }
    }
    return Return;
}
void BinaryTreeFunctions::CountElements(BinaryTreeData* p){
    if(p==head){
        ElementsIdForCounting.clear();
        HowManyElements=0;
    }
    if (p!=nullptr){
       ++HowManyElements;
       ElementsIdForCounting<<QString::number(p->id);
       CountElements(p->Left);
       CountElements(p->Right);
    }
}
void BinaryTreeFunctions::RestoreId(BinaryTreeData* p,BinaryTreeData *parent){
    if (p!=nullptr){
        if(p==head){
            p->id=1;
            p->Parent=nullptr;
        }else{
            if(p==parent->Left)p->id=parent->id*2;
            else p->id=parent->id*2+1;
            p->Parent=parent;
        }
        RestoreId(p->Left,p);
        RestoreId(p->Right,p);
    }
}
BinaryTreeFunctions::~BinaryTreeFunctions(){
    delete head;
}
