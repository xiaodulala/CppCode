#include <iostream>
using namespace std;
const int MAXSIZE=100;
//c++实现顺序存储结构的线性表 类模板
template<typename T>
class SeqList{

public:
    /*
    无参构造，建立一个空的线性表    
    */
    SeqList();
    /*
        有参构造，创建一个长度为n的线性表
    */
   SeqList(int n);

   /*
    析构函数
   */
   ~SeqList();

   /*
     判断是否是空的线性表
   */
  bool IsEmpty();

  /*
    清空线性表
  */
  void Clean();

  /*
    取出线性表中第i个元素
  */
  T GetElem(int i);

  /*
    查询值为e的元素，返回下标i
  */
  int LocateElem(T e);

  /*
    在i的位置插入元素e
  */
  bool Insert(int i,T e);

  /*
    删除第i个元素
  */
  T  Delete(int i);

  /*
    获取线性表的长度
   */
  int Length();

private:
    T m_data[MAXSIZE]; //物理顺序地址大小 容量
    int length; //线性表元素个数 
}
