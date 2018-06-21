/*
 * https://blog.csdn.net/kezunhai/article/details/38417087
 * c++中的explicit关键字
 * 只能用于修饰只有一个参数的类构造函数 他的作用是表明该构造函数是显示的，而非隐士的 跟他对应的另一个关键字implicit 意思是隐藏的类构造函
 * 数默认情况下即为隐藏的(implicit)
 *
 * 1.该关键字只能用来修饰内部的构造函数
 * 2.禁止隐士调用拷贝构造函数
 * 3.禁止类对象之间的隐士转换。
 * 
 * */
#include <iostream>
#include <string.h>
using namespace std;
//隐式转换的例子 一个string类
class Cstring{
public:
//带一个参数的构造函数
	Cstring(int size):m_str(new char[size+1]),m_size(size){
		memset(m_str,0,size+1);
	}
//带一个参数的构造函数(重载版本)
	Cstring(const char* p){
		int size = strlen(p);
		m_str = new char(size+1);
		strcpy(m_str,p);
		m_size = size+1;
	}
	~Cstring()
	{
		delete[] m_str;
	}

	friend ostream& operator<<(ostream& os,const Cstring& s)
	{
		os << s.m_str << endl;
		return os;
	}
private:
	char* m_str;
	int m_size;
};


//不能用隐式转换的类 
class CExplicit{
public:
	explicit CExplicit(int size):m_str(new char[size+1]),m_size(size){}
	explicit CExplicit(const char* p):m_str(strcpy(new char[strlen(p)+1],p)),m_size(strlen(p)){}
	~CExplicit(){delete[] m_str;}
	friend ostream& operator<<(ostream& os,const CExplicit& c){
		os << c.m_str << endl;
		return os;
	}
private:
	char* m_str;
	int m_size;
};


int main ()
{
	//实例化对象
	Cstring string1(20);//ok 调用构造函数1 维护一个内存为20个字符的字符串
	//Cstring string   //nk 没有无参构造函数
	Cstring string3 = 30;//ok 但是写法很怪异 这就是explicit的用法 如果这个构造函数有explicit关键字 这种写法是不行的。
						//注意上面的写法是发生了隐式的类型转换，编译器将 int对象30-->转换成了Cstring对象 Cstring(30) 然后再赋值给string3
	Cstring string4("aaaa");//ok 调用构造函数2
	cout << string4 << endl;

	Cstring string5 = "bbbbb";//ok 同string3 发生了隐式转换
	cout << string5 << endl;

	
	//实例化对象 不可以隐式转换
	CExplicit cString1(20);//ok
	//CExplicit cString2 = 20;//不可以  conversion from ‘int’ to non-scalar type ‘CExplicit’ requested
	CExplicit cString3("cccc");
	cout << cString3;
	//CExplicit cString4 = "dddd";//不可以 conversion from ‘const char [5]’ to non-scalar type ‘CExplicit’ requested


}
