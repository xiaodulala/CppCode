/*
 * 引用型函数参数
 * 1. 引用型函数参数，这时函数形参就是实参的别名 可以通过引用形参来修改实参的值 同时减少函数调用开销
 * 2. 引用型函数参数有可能意外改变实参的值 加const申明为常引用 可以避免意外修改，也可以接收常良型实参
 * */
#include <iostream>
using namespace std;
void swap1(int &x,int &y){
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
}

struct student{
	int age;
	char name[12];
};

void print_student(const student &s){
	cout << s.age << endl;
	cout << s.name << endl;
}

int main ()
{
	int a=3,b=5;
	swap1(a,b);
	cout <<"a=" << a << ",b=" << b << endl;
	student s1 = {16,"张飞"};
	const student s2 = {17,"赵云"};
	print_student(s1);
	print_student(s2);
	return 0;
}
