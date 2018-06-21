/*
 * 运算类的双目操作符重载  + - * /
 * 1.语义的一致性 就是基本类型的时候 + - × / 两边的数和返回值 是左值还是右值 重载后要遵循这个原则
 * 	例如 1+1 a+b 都可以 所以运算类的双目操作符语义一致性一般为：
 * 		表达式结果 必须时候右值  不可以对运算结果再赋值  如 （a对象+b对象)=200; 不返回右值的话，他会调用对象的默认的构造拷贝函数，不允许。
 * 		左操作数和右操作数 可以是左值 也可以是右值。
 * 	实现的两种方式
 * 		成员函数形式 L.operator#(R);
 * 		全局函数形式 operator#(L，R);
 *
 *  例子 用成员函数的形式 完成两个复数对象的相加  复数形式 a+bi   1+2i + 3+4i = 4+6i;
 *  例子 用全局函数的形式 完成两个复数对象的相减
 *
 *
 * 运算类的赋值操作符重载 += -= ×= /=
 * 1.语义的一致性
 * 	 a+=b ==>a = a+b  
 * 	 左操作数是个左值 右操作数可以是左值 也可以是右值
 * 	 表达式的结果是个左值，就是左操作数自身。还可以继续赋值
 *	
 *	实现方式
 *		成员函数形式
 *		全局函数形式
 *	
 *	例子 用成员函数的形式完成 +=操作符重载
 *	例子 用全局函数的形式完成 -=操作符重载
 *
 * */

#include <iostream>
using namespace std;



class Complex{
public:

	Complex(int l,int r):m_l(l),m_r(r){};
	
	//该类的友元函数
	friend const Complex operator-(const Complex&,const Complex&);
	
	void print(void){
		cout << m_l << "+" << m_r << "i" << endl;
	}


	//重载+号操作运算符  成员函数形式
	/*
	 * 左调右参 c1+c2===>  c1.operator+(c2)  c1是调用对象  c2是参数对象 
	 * 几个const的含义
	 * 第一个const  修饰返回值  只能是右值。返回左值就能对其赋值了 不符合+号语义。
	 * 第二个const  常引用   修饰参数对象 也就是右操作数。让右操作数即可以接收左值 也可以接收右值。 如果右值是个常对象 const Complex c2
	 * 						这个时候 如果没有const 函数不会被调用到。
	 * 第三个const  常函数  修饰调用对象 this  也就是c1 左操作数 让左操作数可以接收左值 也可以接收右值 理由同上。
	 * */
	const Complex operator+(const Complex& c)const{
		Complex res(m_l+c.m_l,m_r+c.m_r);
		return res;
	}

	/*
	 * 重载+=操作符 成员函数形式
	 * c1+=c2==> c1.operator+=(c2)
	 * 因为要返回左值自身，所以返回类型加引用
	 * 右操作数可以是左值 也可以是右值 所以加const
	 * 左操作数必须是左值  就是要修改他的值。所以不用const修饰this
	 * 上面实现了+号操作符重载 这里就可以使用
	 * */
	
	Complex& operator+=(const Complex& c2){
		  m_l+=c2.m_l;
		  m_r+=c2.m_r;
		  return *this; 
	}


	/*
	 * 全局函数的形式完成-=操作符重载 
	 * 友元函数可以声明在类的内部 定义在类的外部 在外部可以使用类的任何成员
	 * 友元函数也可以声明 并且定义在类的内部，但是他并不属于类成员函数，他还是一个全局函数。并且没有this指针。
	 *
	 * c2-=c1 ==> operator-=(c2,c1);
	 * */
	friend Complex& operator-=(Complex& c2,const Complex& c1){
		c2.m_l -= c1.m_l;
		c2.m_r -= c1.m_r;
		return c2;
	}



private:	
	int m_l;
	int m_r;
};


//全局函数形式的运算符重载
/* 
 * const修饰原因，和成员函数一样，都是为了满足语义的一致性
 * 注意 在全局函数中，对象直接访问了对象的私有成员变量，这是不可以的。编译器会直接报错。必须在生成对象类中 把这个全局函数声明成
 * 这个类的友元函数 才可以访问该类的私有成员变量
 * 
 * 注意 函数写在类的下面，编译器才认识下面返回值和参数的类型(提醒 按需)
 *
 * 通过friend关键字 可以把一个全局函数	声明为某个类的友元函数  友元函数可以访问类中的任何成员。
 * */

 const Complex operator-(const Complex& c2,const Complex& c1){
	Complex res(c2.m_l-c1.m_l,c2.m_r-c1.m_r);
	return res;
}


int main ()
{
	Complex c1(1,2);
	c1.print();
	Complex c2(3,4);
	c2.print();
	Complex c3 = c1+c2;//成员函数的形式 完成+号运算符重载 c1.operator+(c2);
	c3.print();
	
	c3 = c2-c1;
	c3.print();//全局函数的形似 完成-号运算符的重载 operator+(c1+c2);

	c1+=c2;//成员函数的形式 完成+=号运算符重载 c1.operator+=(c2);
	c1.print();

	c2-=c1;//全局函数的形式 完成-=号运算符重载  c2.operator-=(c1);
	c2.print();
	return 0;
}


