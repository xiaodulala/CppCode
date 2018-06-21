/*
* 类型转换构造函数 也叫但参构造函数
* 完成隐式转换
× 如果不许出现29行的写法，不允许编译器调用隐士的类型转换构造函数 需要对类型转换构造函数加explicit关键字修饰 要求必须显示的完成对象转换。
*/

#include <iostream>
using namespace std;
class Intenger{
public:
	Intenger(void):m_data(10){}

	//这个是类型转换构造函数 也叫单参函数。 目标类型  参数是源目标类型
	explicit Intenger(int data):m_data(data){
		cout << "类型转换构造函数" << endl;
	}
	void print(){
		cout << m_data << endl;
	}
private:
	int m_data;
};

int main ()
{

	Intenger i; //这里调用自己写的无参构造函数
	i.print();//10
	//加上explicit 29行会报错  需要显示的转换 
//	i = 100;//注意这句话 编译器会通过  这是因为编译器会调用Intenger的类型转换构造函数 让100-->Intenger对象的转换。
	i.print();

	//一下都属于显示的类型转换，都会调用类型转换构造函数
	i = (Intenger)200;//c风格
	i = Intenger(300);//c++风格
	i.print();
	return 0;
}
