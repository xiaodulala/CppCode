/*
 * 虚继承
 * 公共基类A对象 在汇聚子类D对象中会存在多个实例，在通过子类访问公共基类中的成员，会因为继承路径不同，导致结果不一致。
 * 一个是通过B对象实例化的A对象  一个是C对象实例化的A对象。在汇聚子类D对象中调用get_data 访问的是由B对象继承时初始化的A对象
 * 在汇聚子类对象中调用set_data的时候，访问的是由C对象继承时初始化的A对象。
 *
 * 解决：
 * 	通过虚继承，可以让公共基类A对象在汇聚子类D对象中实例唯一，并且为所有中间子类共享(B C)。这样 即使沿着不同的继承路径，所访问到公共成员
 * 	一定是一致的。
 *
 * 	语法要求：
 * 	在继承表中使用virtual关键字
 * 	唯一末端的D子类负责构造公共基类子对象。注意，虽然公共基类对象A由D子类构造，但是A的多有子类 bcd都必须在构造函数中显示指明其初始化方式
 * 	否则编译器将用无参的方式来初始化对象。
 * 
 *
 * 虚继承实现的原理
 * 构造函数中的类大小输出如下  
 * 	A 4    B 16   C 16  D 24
 * 	A中只有一个m_data 所以对象是4个字节
 * 
 * B中多了一个指针类型的变量 叫虚表指针，因为是虚继承，其实在B的内部是无法直接访问m_data的。在虚表指针中记录了对象B到A对象的便宜量。
 * 	当访问m_data时，需要通过对象的地址加上指针中的便宜量地址，从而找到m_data来访问。 现在是64位机，指针类小大小为8个字节，加上继承的
 * 	m_data是4个字节，但是要进行数据对齐 8+8 是16个字节
 *
 * C同B
 *
 * D对象 两个虚表指针 8+8=16+(4+数据对齐(4)) =24
 *
 * */


#include <iostream>
using namespace std;

//公共基类
class A{
public:
	A(int data):m_data(data){
		cout << "A::A()" << sizeof(*this) << endl;
	}
	int m_data;
};

//A的一个子类
class B:virtual public A {
public:
	B(int data):A(data){
		cout << "B::B()" << sizeof(*this) << endl;
	}//虽然A由D子类构造，单这里也不能少。
	int get_data(void){
		return m_data;
	}
};

//A的另一个子类
class C:virtual public A{
public:
	C(int data):A(data){
		cout << "C::C()" << sizeof(*this) << endl;
	}//这里也不能少。
	void set_data(int data){
		m_data = data;
		return ;
	}
};


//汇聚子类 构成钻石继承。
class D:public B,public C{
public:
	D(int data):B(data),C(data),A(data){
		cout << "D::D()" << sizeof(*this) << endl;
	}//一定注意 A类对象其实是在D类对象中构造，所以钻石继承的末端子类必须在初始化表中构造公共基类A
};


int main ()
{
	//实例化D对象
	D  d(100);
	cout << d.get_data() << endl;
	/*
	 * 	
	 * */
	d.set_data(200);
	/*
	 * 设置data为200,但是输出还是100. 这是因为在汇聚子类中有多个实例，又两个A对象实例。
	 * 在通过子类bc方位公共基类的成员的时候，因为继承路径不同
	 * 导致结果不一样。所以要设置虚继承。
	 * 虚继承可以让公共基类A对象在汇聚子类中实例唯一。这样访问到的A对象中的m_data是一个。
	 * */
	cout << d.get_data() << endl;
	return 0;
}



