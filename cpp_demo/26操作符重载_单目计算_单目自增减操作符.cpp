/*
 * 单目操作符
 * 计算类 - ~
 * 语义：
 * 	左操作数是即可以是左值也可以是右值  -a -10
 * 	返回值是右值  不能在进行赋值。 -10=100 error
 * 自增减 前++--  后++--
 *	前++--
 *	操作数是左值 要修改他自身的值。右值不能修改，只能是左值。
 *	返回值是左值，就是操作数自身。 ++++a;
 *	
 *	后++--
 *	操作数是左值 要修改他自身的值。
 *	返回值是右值 返回操作数在增加前的副本。
 *	为了与前++--操作符重载区分 后++--重载函数要加哑元参数
 *
 *	例子
 *	1.成员函数实现-操作符重载
 *	2.全局函数实现~操作符重载  自定义计算为乘方
 *	3.成员函数实现前++重载
 *	4.全局函数实现前--重载
 *	5.成员函数实现后++重载
 *	6.全局函数实现后--重载
 *
 * */

#include <iostream>
using namespace std;
class Integer{
public:
	Integer(int data=0):m_data(data){};
	void print(void){
		cout << m_data << endl;
	}
	//成员函数实现- -i==> i.operator(void)const{}
	const Integer operator-(void)const{
		Integer res(-m_data);
		return res;
	}
	//全局函数实现~
	friend const Integer operator~(const Integer& i){
		Integer res(i.m_data*i.m_data);
		return res;
	}

	//成员函数实现前++ i.operator(void){}
	// 返回值是操作数本身，必须左值  操作数要更改自身的值 必须左值
	Integer& operator++(void){
		++m_data;
		return *this;
	}

	//全局函数实现前——
	friend Integer& operator--(Integer& i){
		--i.m_data;
		return i; 
	}

	//成员函数实现后++ i.operator++(int){}
	//操作数必须是左值 要更改自身的值。返回值必须是右值 不能再赋值
	const Integer operator++(int){
		Integer old = *this;
		++(*this);
		return old;
	}

	//全局函数实现后--
	friend const Integer operator--(Integer& i,int){
		Integer old = i;
		--i;
		return old;
	}
private:
	int m_data;
};


int main ()
{
	Integer i(10);
	Integer j = -i; //这个时候i的值是不变的 -i i不变 整个表达式的值是-i的结果
	j.print();
	Integer c = ~i;//实现乘方
	c.print();

	++++i;
	i.print();
	----i;
	i.print();

	i++;//返回值是i子增前的副本
	i.print();
	i--;
	i.print();

	return 0;
}

















