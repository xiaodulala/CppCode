/*
 * c++中动态分配内存 new delete new[] delete[] 运算符的使用
 * 
 * c++中的动态分配内存和c中的malloc和free的区别？
 * 1.首先 maclloc是c中的库函数 而new和delete是运算符
 * 2.malloc 分配内存的时候是以分配字节数量为主，可以随意分配。而new运算符分配内存是以类型为主 这样可以更有跨平台性并且还可以避免内存的浪费。
 * 3.new可以直接初始化内存数据 
 * 4.异常处理不通 malloc分配失败返回NULL new分配失败会发出异常信号 等待程序捕获。
 * */

#include <iostream>
using namespace std;

int main ()
{
	//使用new分配内存
	int *pi = new int;//new运算符分配针对的是类型
	*pi = 22;
	cout << *pi << endl;
	//使用完以后要释放内存避免内存泄漏
	delete pi;
	//指针置空 避免野指针
	pi = NULL;

	//使用new分配内存 并且可以直接初始化内存数据
	int *pa = new int(23);
	(*pa)++; //++的优先级高于* 如果写成*pa++ 会造成指针越界使用  指向后面4个字节的地址
	cout << *pa << endl;
	delete pa;
	pa=NULL;
	
	//使用new分配连续内存  数组形式 
	int *parr = new int[5];
	//int *parr = new int[5]{1,2,3,4,5};//这样也可以对数组进行初始化 但是需要支持c++11标准
	//数组赋值
	for(int i=0;i<5;i++)
		parr[i]=i+1;
	for(int i=0;i<5;i++)
		cout << parr[i] <<  ' ';
	cout << endl;
	//释放内存
	delete[] parr; 
	parr = NULL;

	

	return 0;
}
