/*
*	无参构造函数  又叫默认构造函数
*	如果一个类里没有任何构造函数，编译器会提供一个缺省的无参构造函数
*		--> 无参构造函数，对与基本类型的成员变量 不会做c初始化
*		--> 无参构造函数，对于类类型的成员变量(成员子对象),会自动调用相应类型的无参构造函数
*	注意：如果定义了构造函数，无论是否又参数，都不会在调用无参构造函数


*/

class A {
public:
	A(void):m_i(2){}
	A(int i):m_i(i){}
	int m_i;
};

class B{
public:
	int m_data; //成员变量
	A a;//成员子对象
};

#include <iostream>
using namespace std;




int main()
{
	B b;
	cout << b.m_data << endl;//这是一个不确定的数 b调用的是无参构造函数，不会实例化m_data这个成员对象
	cout << b.a.m_i << endl;//这个是2,应为a是b的成员子对象，所以b会调用a的无参构造函数
	return 0;
}
