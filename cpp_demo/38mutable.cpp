/*
 * mutable 可变的 const的反意词
 * 被mutable修饰的的变量 可以突破const的限制
 * */

#include <iostream>

using namespace std;

class A{
public:
	A(const int times):m_times(times){}
	void add_time()const{ //常成员函数 说明不会更改类中的成员变量的值 但是可以更改被mutable修饰的成员变量
		m_times++;
	}
	int  get_times()const{
		return m_times;
	}
private:
	mutable int m_times;

};

int main()
{

	A a(20);
	a.add_time();
	cout << a.get_times() << endl;
	return 0;
}
