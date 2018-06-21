/*
 * 用来初始化类中的成员  
 *
 * 例子 需要显示使用初始化表的场景(也就是必须使用初始化表)
 * 1.当类中又类类型的成员变量(成员子对象的),并且该成员类又没有无参构造函数 则必须通过初始化表来完成该成员子对象的初始化
 * 2.类中包含有const 或者 引用&类型的成员变量的时候 必须在初始化表中进行初始化 因为const和&在定义变量的时候必须初始化
 * 
 * 注意：成员变量的初始化顺寻，又他们在类中的声明顺序决定，与初始化表的顺序无关。
 * 		所以 不要用一个成员变量去初始化另一个成员变量，小心因为初始化的顺序而出现错误 
 * */

//成员变量中又成员子对象 并且成员类中没有无参构造函数  必须使用初始化表
#include <iostream>
#include <cstring>
using namespace std;
class A{
public:
	A(int data):m_data(data){}//这个类中没有无参构造函数
	int m_data;
};

class B{
public:
	B(int n):m_n(n),m_a(123){} //这里必须对成员对象m_a在初始化列表中初始化
	A m_a;
	int m_n;
};

class C{
public:
	C(int data,int& i):m_data(data),m_i(i){} //成员变量中又const或者& 必须在初始化列表中进行初始化
	const int m_data;
	int& m_i;
};

class foo{
public:
	foo(const char *str):m_str(str?str:""),m_len(strlen(str?str:"")){}//不可以用自己的成员变量去实例化另一个成员变量 像这样 ：m_len(m_str.length)
	size_t m_len;
	string m_str;
};

int main ()
{
	B b(100);
	cout << b.m_n << endl;
	cout << b.m_a.m_data << endl;

	int i = 200;
	C c(11,i);
	cout << c.m_data << endl;
	cout << c.m_i << endl;

	const char* str="hello world";
	foo f(str);
	cout << f.m_str << endl;
	cout << f.m_len << endl;

	return 0;
}
