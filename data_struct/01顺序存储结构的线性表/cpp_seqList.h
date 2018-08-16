/*
  c++实现顺序物理结构线性表
  duyong
*/
#include <iostream>
using namespace std;
const int MAXSIZE=20;
//定义数据域类型 暂时使用int类型代替 后续改成类模板 
typedef int ElemType;
typedef struct{
    ElemType data[MAXSIZE];
    int length;
}SeqListType;

class SeqList{
public:
    SeqList();
    ~SeqList();
    void CreateList(ElemType data[],int n);
    void ListInit();
    void ListClear();
    int  ListLength();
    bool ListEmpty();
    bool GetElem(int i,ElemType& e);
    int LocateElem(ElemType e);
    bool ListInsert(int i,ElemType e);
    bool ListDelete(int i,ElemType& e);
    void ListPrint();
private:
    SeqListType* m_list;
};


