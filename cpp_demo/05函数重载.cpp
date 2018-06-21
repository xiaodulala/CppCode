/*
 * 演示函数重载中的转换优先级
 *  完全匹配 > 常量转换 > 升级转换 > 降级转换 > 省略号匹配
 * */
#include <iostream>
using namespace std;


//char-->int  升级转换
void bar(int a){
	cout << "bar(int a)" << endl;
}


//char-->const char 常量转换
void bar(const char a){
	cout << "bar(const char a)" << endl;
}


//short-->int 升级转换
void func(int num){
	cout << "func(int num)" << endl;
}

//short-->long long int  过分的升级转换 如果没有上面的func升级转换函数 这个函数也不会被匹配 编译器觉得太浪费内存了。
void func(long long num){
	cout << "func(long long num)" << endl;
}

//short-->char  降级转换
void func(char num){
	cout << "func(char num)" << endl;
}

//省略号匹配
void demo(int a,...){
	cout << "demo(int,...)" << endl;
}
//double-->float  降级转换
void demo(int a,float b){
	cout << "demo(int,float)" << endl;
}

int main ()
{
	char a = 'A';//验证  常量转换 > 升级转换
	bar(a);
	short b=128;//验证升级转换 > 降级转换
	func(b);
	demo(10,3.14);//验证降级转换 > 省略号匹配

}

