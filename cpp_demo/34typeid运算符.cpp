/*
 * typeid运算符的使用
 * 返回一个typeinfo对象 用于描述类型信息 typeinfo对象中的name()成员函数可以获取字符串形式类型信息
 *
 * 还可以用来确定多态特性 实际的对象类型
 *
 * */


#include <iostream>
#include <typeinfo>
using namespace std;

class A{};
class B:public A{};
class C:public A{};

void func(A& a){
	cout << typeid(a).name() << endl;
	cout << typeid(B).name() << endl;
	if(typeid(a)==typeid(B)){
		cout << "执行是B类型的逻辑" << endl;
	}else if(typeid(a)==typeid(C)){
		cout << "执行是C类型的逻辑" << endl;
	}
}

int main()
{


	//应用场景1
	int i;
	cout << typeid(int).name() << endl;//i
	cout << typeid(i).name() << endl;//i
	
	int* arr1[5]; //数组指针： arr1是一个数组，有五个元素 每个元素是个指针，指针指向的类型是int
	int (*arr2)[5];//指针数组: arr2是一个指针，指向一个数组 数组有五个元素 是int类型

	cout << typeid(arr1).name() << endl;//A5_Pi  数组 5元素 指针 指向int 
	cout << typeid(arr2).name() << endl;//PA5_i  指针 指向数组 数组5元素 int类型

	cout << typeid(int(*[5])(int)).name() << endl;//函数指针数组  A5_PFiiE 是个数组 里面又五个元素 每个原始是一个指针，指针指向的是一个函数
												//函数返回值是i 参数是i 完了。
	
	B b;
	C c;
	func(b);
	func(c);

	return 0;
}
