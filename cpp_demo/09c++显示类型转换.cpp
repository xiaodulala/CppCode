/*
 * c++中的显示类型转换
 * 1.静态类型转换 适用于将void* 转换成其他指针类型
 * 2.常类型转换 用于取出指针或引用的常属性
 * 3.动态类型转换
 * 4.重解释类型转换 
 *
 * */

#include <iostream>
using namespace std;

int main ()
{

	//静态类型转换例子
	int a=10;
	void *pv=&a;//万能指针，c和c++都允许void*指针指向a的地址
	int *pi = static_cast<int *>(pv);//c++ 必须将void* 转换成int* 使用静态类型转换

	const volatile  int b=200;//使用volatile关键字 告诉编译器 每次这个变量都从内存读取 不做寄存器的副本操作。
	int *pb =const_cast<int *>(&b);
	*pb=300;
	cout << b << endl;
	cout << *pb << endl;
	cout << (void *)&b << endl;
	cout << pb << endl;



	return 0;
}
