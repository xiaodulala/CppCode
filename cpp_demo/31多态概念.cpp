/*
 * 多态概念
 * 如果将基类中某个成员声明为虚函数，那么其子类具有相同原型的成员函数也是虚函数(自动变虚) 并且对基类中的版本形成覆盖。
 * 这时通过指向子类对象的基类指针，或者引用子类对象的基类引用 调用虚函数的时，实际被执行的将是子类的覆盖版本 这是多态。
 *
 * 函数重写的要写(虚函数覆盖条件)
 * 只有类的成员函数才能声明为虚函数 全局函数，静态成员函数 和构造函数都不能声明为虚函数 析构函数除外
 * 必须是基类中的成员，必须带virtual关键字
 * 虚汗数在子类的覆盖版本，必须和基类中的原始版本拥有相同的函数签名：即函数名 参数表(类型和个数)和常属性
 * 如果基类中的虚函数返回的是基本类型，那么子类的覆盖版本必须返回相同类型
 * 如果基类中的虚函数返回的是类类型的指针或者引用 那么允许子类的覆盖版本返回其子类类型的指针或者引用--类型协变(隐藏向上造型)
 *
 * 多态条件
 * 1.必须满足覆盖条件
 * 2.必须通过指针或者引用调用虚函数，才能表现出来
 * 3.调用虚函数也可以是this指针，只要他是一个指向子类对象的指针，同样可以表现出多态的特性 //重点 看列子
 *
 *
 * ubuntu test
 * */


#include <iostream>
using namespace std;

/*
 * 图形基类
 * */

class Shape{
public:	
	Shape(int x,int y):m_x(x),m_y(y){};
	virtual void draw(void){
		cout << "画图形:" << "x:" << m_x << ",y:" << m_y << endl;
	}
protected:
	int m_x;
	int m_y;
};

/*
 * 长方形子类
 * */
class Rect:public Shape{
public:
	Rect(int x,int y,int w,int h):Shape(x,y),m_w(w),m_h(h){};
	/*virtual*/ void draw(void){
		cout << "画矩形:" << "x:" << m_x << ",y:" << m_y << ",w:" << m_w << ",h" << m_h << endl;
	}
protected:
	int m_h;
	int m_w;
};

/*
 * 圆形
 * */
class Circle:public Shape{
public:
	Circle(int x,int y,int r):Shape(x,y),m_r(r){}
	/*virtual*/ void draw(void){
		cout << "画圆形:" << "x:" << m_x << ",y:" << m_y << ",r:" << m_r << endl;
	}
protected:
	int m_r;
};



/* this指针作为指向子类对象的基类指针 
 * this指针的类型，本来就是该类类型。
 * this指向的对象，是指调用对象。
 * */
class Base{
public:
	virtual void run(void){}
	void start(void){ //在这里形成多态。this指针的类型Base* this 调用者是基类对象。this指向的对象是基类对象。
		run();
	}
protected:
	int m_i;
};

class Derive:public Base{
	void run(void){
		cout << "Derive::run()" << endl;
	}
};


int main (){
	//使用基类指针指向子类对象
	Shape* arr[1024]={NULL};//指针数组，是一个数组，数组里每一个成员是一个Shape类型的指针。
	arr[0]= new Rect(0,0,100,100);
	arr[1]= new Circle(0,0,200);
	for(int i=0;i<2;i++){
		arr[i]->draw();
	}

	//使用引用子类对象的基类引用
	Rect rect(100,100,200,200);
	Shape& r_rect = rect;
	r_rect.draw();

	//this指针作为 指向子类对象的指针 调用虚函数 产生多态
	Derive d;
	d.start();

	cout << sizeof(arr) << endl;
	return 0;
}
