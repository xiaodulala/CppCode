/*
 * 常成员函数 在成员函数的后面加const  修饰的是this指针
 * 常函数中的this指针是一个常指针，不能用在常函数中修改成员变量的值  被mutable修饰的成员变量除外
 * 非 常对象可以调用非 常函数，而常对象只能调用常函数
 *
 * 函数名和参数表相同的成员函数 其常版本和非常版本可以构成函数重载
 * */

#include <iostream>
using namespace std;
class test{
public:
	test(int data,int age):m_data(data),m_age(age){};
	void show() const {
		//cout << m_data++ << endl; 这行直接报错 常成员函数不可修改成员变量的值
		cout << m_data << endl;
		cout << ++m_age << endl;
	}
private:
	int m_data;
	mutable int m_age;
};


class A{
public:
	void func(void){} //如果显示this指针 这个函数应该是 void func(A* this){}
	void func1(void) const {};	//void func(const A* this){}  常成员函数
};

int main ()
{
	test t(10,20);
	t.show();
	A a; //a是非常对象
	a.func();//可以调用非 常函数 ok
	a.func1();//可以调用 常函数 ok 缩小对内存的操作 安全
	const A a2=a;// 这是一个常对象
	//a2.func(); //常对象 调用非常函数  不可以 扩大了对内存的操作 不安全 error
	a2.func1();//常对象 调用 常函数 ok
	return 0;
}
