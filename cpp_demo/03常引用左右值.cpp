/*
 * 常引用 
 * 定义引用时用const修饰  不能通过引用修改引用目标的值
 * 普通的引用 只能引用左值 常引用既能引用左值 也可以引用右值 也叫万能引用
 *
 * 左值和右值
 * 左值
 * 	变量一般是左值
 * 	赋值表达式结果是左值
 * 	前++/-- 结果是左值
 * 右值
 * 	常量 带const的变量 是右值
 * 	函数返回值是右值
 * 	大多数表达式是右值
 *
 * */

#include <iostream>
using namespace std;

int func(void){
	int a = 100;
	//函数中返回局部变量  函数结束 函数的栈帧会被释放 包括a变量  return 语句会用一个临时变量保存a的值 这个临时变量叫做将亡右值 返回给调用函数 
	//调用函数如果想用引用接收这个临时变量 必须使用常引用 因为临时变量是一个右值
	return a;
}

int main ()
{
	//int &a = 100;//error  non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int' 100是常量 不可以被变量a引用
	const int &a = 100;//ok 变量a是常引用  可以引用右值
	const int &b = func();
	cout << a << endl;
	cout << b << endl;
	return 0;
}
