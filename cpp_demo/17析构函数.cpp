/*
 * 析构函数
 * ~类名 没有返回值 没有参数 不能重载
 *
 * 调用时机：对象销毁时被调用
 * 对象声明时候销毁？
 * 1.栈对象当离开作用域时 其析构函数被作用域终止运算符调用
 * 2.堆对象的析构函数被delete运算符调用
 *
 * 没有析构函数 系统会提供
 * 
 * 缺省析构函数对于基本类型的成员变量 社么都不做。对成员子对象，会调用成员子对象的析构函数
 * */

#include <iostream>
using namespace std;
class A{
	public:
	~A(void){
		cout << "A::~A(void)" << endl; 
	};
};

int main (){
	{
		A a;
		cout << "test1" << endl;
		A* p_a = new A;
		delete p_a; //A::~A(void)
		p_a=NULL;
		cout << "test2" << endl;
	} //A::~A(void)
	cout << "test3" << endl;
	return 0;
}
