/*
 * this指针
 * 类中成员函数，隐藏该类类型的指针参数 叫this
 * 	对于普通成员函数，this指针指向调用该函数的对象
 * 	对于构造函数 this指针指向正在创建的对象
 * 需要显示使用this的场景
 * 1.区分作用域 行参和成员变量名称相同，那么使用this指向的一定是成员变量
 * 2.返回自引用 从成员函数中返回调用对象的自身
 * 3.从类的内部销毁对象自身。
 *
 * */
#include <iostream>
using namespace std;
class Counter{
public:
	Counter(int data=0):m_data(data){}
	Counter& add(void){
		++m_data;
		return *this;//返回自引用
	}
	int m_data;
};

int main ()
{

	Counter cn;
	cn.add().add().add();
	cout << cn.m_data << endl;
	return 0;
}
