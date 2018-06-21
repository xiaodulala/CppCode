/*
 * 静态成员函数
 * 1.静态成员函数和普通成员函数一样，都在代码段。但是静态成员函数没有this指针，也没有const属性
 * 2.使用方法 类名::静态成员函数  相当于是被限制在类的内部的全局函数。
 * 静态成员函数中 只能访问静态成员变量，不能访问非静态成员变量。因为静态成员函数没有this指针，而非静态成员变量必须在对象产生的情况下 通过
 * this指针来调用，所以静态成员函数不能调用。 非静态成员函数 可以调用静态成员变量和非静态的成员变量。
 * 理解：从内存角度，非静态成员变量是在对象产生的时候，才会被分配内存，如果你直接通过类名调用静态成员函数，在静态成员函数中访问非静态的成
 * 员变量，这时候还没有对象呢。非静态成员变量也没有被分配内存，所以调用是失败的。 
 * */

#include <iostream>
using namespace std;

class A{
public:
	A(int data=100):m_data(data){}
	void func1(){
		cout <<  "非静态成员函数" << endl;
		cout << m_data << endl;
		cout << s_data << endl;
	}
	
	static void func2(){
		cout << "静态成员函数" << endl;
		//cout << m_data << endl;//这句话将报错 静态成员函数中 不能调用非静态成员变量
		cout << s_data << endl;
	}

private:
	int m_data;
	static int s_data;
};
int A::s_data = 200;



int main ()
{
	//通过类名直接调用静态成员函数
	A::func2();
	A a1;
	a1.func1();//非静态成员函数 可以调用静态成员变量，也可以调用非静态成员变量
	//a1.func2(); 就算通过对象调用静态成员函数，也不可以。因为静态成员函数没有this指针，对象也不会被传递给静态成员函数
	return 0;
}
