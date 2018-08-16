#include "cpp_seqList.h"

SeqList::SeqList()
{
    ListInit();
}

SeqList::~SeqList()
{
    delete m_list;
    m_list  = NULL;
}

void SeqList::CreateList(ElemType data[],int n)
{
    for (int i=0;i<n;i++)
        m_list->data[i]=data[i];
    m_list->length = n;
    return;
}

void SeqList::ListInit()
{
    m_list = new SeqListType;
    m_list->length = 0;
}

bool SeqList::ListEmpty()
{
    return m_list->length == 0;
}

void SeqList::ListClear()
{
    if(ListEmpty())
        return;
    delete m_list;
    ListInit();
}

int  SeqList::ListLength()
{
    return m_list->length;
}

bool SeqList::GetElem(int i,ElemType& e)
{
    if (i <1 || i > m_list->length)
        return false;
    e = m_list->data[i-1]; //逻辑位序转为物理位序
    return e;
}

int SeqList::LocateElem(ElemType e)
{
    int i = 0;
    while(i<m_list->length && m_list->data[i]!=e)
        i++;
    if(i>=m_list->length)
        return 0;//没找到
    else 
        return i++; //得到的是物理位序，要返回逻辑位序 从1开始
}


bool SeqList::ListInsert(int i,ElemType e)
{
    if (i<1 || i> m_list->length)
        return false;
    i--;//逻辑位序变为物理位序
    for(int j=m_list->length;j>i;j--)
        m_list->data[j] = m_list->data[j-1]; //全部后移一位
    m_list->data[i]=e;
    m_list->length++;
    return true;
}

bool SeqList::ListDelete(int i,ElemType& e)
{
    if (i<1 || i> m_list->length)
        return false;
    i--;
    for (int j=i;j<m_list->length;j++)
        m_list->data[j]=m_list->data[j+1];
    m_list->length--;
    return true;
}

void SeqList::ListPrint()
{
    if (ListEmpty())
        return;
    for(int i=0;i<m_list->length;i++)
        cout << m_list->data[i] << " ";
    cout << endl;
}



int main()
{
    ElemType  data[]={10,20,30,40,50};
    SeqList list;
    list.CreateList(data,5);
    list.ListPrint();

    cout << list.ListLength() << endl;

    ElemType e;
    list.GetElem(5,e);
    cout << e << endl;

    list.ListInsert(2,60);

    list.ListPrint();

    list.ListDelete(3,e);
    cout << e << endl;
    list.ListPrint();

    return 0;
}



