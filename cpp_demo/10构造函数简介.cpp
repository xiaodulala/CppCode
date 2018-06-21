/*
 * 构造函数的特点
 *  和类名相同 没有返回值  注意是没有返回值 
 *  构造函数是由编译器自动调用的 不可以显示的调用构造函数
 *  构造函数的作用  主要用来初始化对象  其实就是初始化类中的成员变量
 * */
#include <iostream>
using namespace std;
class Student{
public:
	Student(string const& name):m_name(name){}

	void who(){
		cout << "name:" << m_name << endl;
	}
private:
	string m_name;
};


int main(void)
{
	//实例化对象的时候 构造函数会自动调用
	Student s("Tom");//在栈区创建对象
	s.who();
	Student s1= Student("obama");//同样也是创建对象
	s1.who();
	Student arr[3]={Student("zhangfei"),Student("libai"),Student("likui")};//对象数组
	arr[0].who();
	arr[1].who();
	arr[2].who();
	return 0;
	
}


