/*
 * 拷贝函数的浅拷贝和深拷贝
 * 1.如果一个类中包含指针类型的成员变量	 缺省的构造函数只是复制了指针变量本身 而没有复制指针所指向的数据 这种拷贝叫做浅拷贝
 * 2.浅拷贝导致不同对象之间数据共享，如果数据在堆区，可能会在析构过程中产生double free的错误 因为必须自己定义一个支持复制指针指向数据的拷贝
 * 函数 这叫深拷贝
 *
 * */
#include <iostream>
#include <cstring>
using namespace std;

class String{
public:
	//构造函数
	String(const char *str):m_str(strcpy(new char[strlen(str)+1],str)){}
	//析构函数
	~String(void){
		delete[] m_str;
		m_str=NULL;
	}

	//这个是浅拷贝，只是拷贝了指针本身 而没有拷贝指针指向的数据
	//String(const String& that):m_str(that.m_str){}

	//拷贝构造函数--深拷贝 可以完成对指针数据的复制
	String(const String& that):m_str(strcpy(new char[strlen(that.m_str)+1],that.m_str)){}

	//访问函数
	const char* c_str(void) const{
		return m_str;
	}
private:
	char *m_str;
};


int main (){
	String s1("hello world");
	cout << s1.c_str() << endl;
	String s2(s1);
	cout << s2.c_str() << endl;
	return 0;
}
