/*
 * 虚析构函数
 *  
 * 场景：
 * 基类的析构函数 不会调用子类的析构函数 对一个指向子类对象的基类指针使用delete运算符 实际被执行的仅仅是基类的析构函数 而子类的析构函数
 * 不会被执行，又内存泄漏的风险。
 *
 * 解决：
 * 可以将基类的析构函数声明为虚函数 那么子类的析构函数也是一个虚函数 并且对基类的析构函数形成有效的覆盖，可以表现出多态的语法行
 * 这时delete一个指向子类对象的基类指针 实际被执行的将是子类的析构函数 子类析构函数又会自动调用基类的析构函数
 * 这样可以保证父子类的动态资源都可以被释放 避免内存泄漏
 *
 * */
#include <iostream>
using namespace std;
class Base{
public:
	Base(void){
		cout << "基类:分配了动态内存资源" << endl;
	}
   virtual ~Base(void){
		cout << "基类:释放动态内存资源" << endl;
	}
};

class Derive:public Base{
public:
	Derive(void){
		cout << "子类:分配动态资源" << endl;
	}
	~Derive(void){
		cout << "子类:释放动态资源" << endl;
	}
};

int main()
{
	Base* pb = new Derive;
	delete pb; //deltete运算符会调用指针类型的析构函数。现在指针类型是基类指针，所以会直接调用基类的析构函数。但是对象是子类对象，里面
				//也有子类的动态资源分配，子类的析构函数是无法被调用的。  如果基类析构函数是虚函数，那么会形成动态语法，delete的时候
				//调用的是子类的析构函数，根据对象销毁的流程我们知道，子类析构函数执行完毕后会自动调用基类的析构函数 这样就把父子类的
				//析构函数全部调用了，避免了内存泄漏。
	return 0;
}
