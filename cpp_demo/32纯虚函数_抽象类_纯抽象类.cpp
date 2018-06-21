/*
 * 纯虚函数
 * virtual 返回类型 函数名(行参表)[const]=0;
 * 抽象类
 * 如果一个类包含了纯虚函数，那么该类就是抽象类
 * 注意 抽象类不能创建对象。类的抽象属性可以被继承 如果子类没有覆盖基类中的纯虚函数 那么该类也是一个抽象类 不能被实例化成对象
 *
 * 纯抽象类 如果一个类中除了构造函数和析构函数 所有成员函数都是纯虚函数 那么该类就是纯抽象类 也叫接口类
 *
 * 
 * */


#include <iostream>
using namespace std;

//Base就是纯抽象类 不能被实例化为对象
class Base{
public:
	Base(int i=0):m_i(i){}
	~Base(void){}
protected:
	int m_i;
public:
	virtual void func(void)=0;//纯虚函数
	virtual void func1(void)const=0;//纯虚函数
};

class Derive:public Base{
public:
	Derive(int i):Base(i){}
	~Derive(void){}
protected:
	void func(void){
		cout << "func" << endl;
	}

	void func1(void)const{
		cout <<"func1" << endl;
	}
};

int main()
{

	Base* p_b= new Derive(10);
	p_b->func();
	p_b->func1();

	return 0;

}
