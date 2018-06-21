/*
 * 注意 引用型函数的参数返回值 不能是一个局部变量
 *
 * */

#include <iostream>
using namespace std;
//静态变量作为引用返回
const int &func1(){
	static int a = 100;
	return a;
}


//结构体成员变量作为引用返回
struct func2{
	int data;
	int &get_data(void){
		return data;
	}
};


//这是不对的 
/*int &func3(){
	int a = 200;
	return a;
}*/

int main ()
{
	//引用型返回值返回左值
	cout << func1() << endl;
	struct func2 f2;
	f2.data = 100;
	f2.get_data() = 200;
	cout << f2.data << endl;
	return 0;
}
