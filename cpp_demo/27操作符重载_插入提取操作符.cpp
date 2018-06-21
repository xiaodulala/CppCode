/*
 * 插入<< 提取 >> 操作符重载
 * 
 * 分析：<<插入操作符
 * 	cout << a自定义对象 << 10 << endl; 类似这样的操作，要输出a对象。他相当与是个双目操作符。
 *  操作符左边是一个系统类实例化出来的对象 ostream cout,右边是用户自定义的对象或者是个常量。
 * 根据左调右参的形式，重载函数应该写成  cout.operator<<(a); 我们应该把重载函数写到调用对象的类中，现在cout的类是系统类ostream 是c++标准
 * 库的类，我们不能修改。所以只能写成全局函数的形式。如 operator(ostream& os,const a& a); 这个时候，还又一个问题，写成全局函数形式的时候
 * a类中的私有成员无法访问，所以需要在a类中加友元函数。让这个全局函数能构访问a类中的私有成员。 
 * 因为友元函数可以在a类中声明，类外实现，也可以直接在a类中声明并且实现，我们通常一般把这个友元函数写在类中。但是 他还是一个全局函数
 *
 * 分析语义：
 * 	返回值一定还是cout这个输出对象自身，否则没办法左连贯操作，返回值肯定是左值。
 * 	左操作数  也就是ostream类实例化出来的cout对象，他的值会发生改变，所以只能是左值，不能是右值。
 * 	右操作数  技能输出变量，也能输出常量。所以即可以是左值，也可以是右值。
 * 	 
 *
 * 分析：>> 提取操作符
 * 	 同<<。
 * 分析语义：
 * 	返回值一定是输入对象自身。是个左值。
 * 	左操作数是个左值，他的值会发生改变。其实就是他维护的那快内存会发生改变，数据被提取走了。
 * 	右操作数 必须是左值，也就是说必须是变量。才能接受提取到的值。常量不能提取值。
 *
 * */

#include <iostream>
using namespace std;

class Student{
public:
	Student(string name,int age):m_name(name),m_age(age){};
private:
	string m_name;
	int m_age;
	//全局方式的插入符<< 重载函数
	friend ostream& operator<<(ostream& os,const Student& s){
		os << s.m_name << ":" << s.m_age << endl;
		return os;
	}
	friend istream& operator>>(istream& is,Student& s){
		is >> s.m_name >> s.m_age;
		return is;
	}
};

int main ()
{
	Student s1("duyong",30);
	cout << s1; //直接输出对象 需要重载插入操作符


	Student s2("zhangfei",27);
	cout << "请输入姓名和年龄:";
	cin >> s2;
	cout << s2;
	return 0;
}
