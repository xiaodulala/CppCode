/*
 * 拷贝赋值
 * 编译器会为c++类中提供一个缺省的拷贝赋值函数 完成两个对象的赋值操作 如a=b 可以被编译器翻译成 a.operator=(b) 左值是调用对象 右值是
 * 		对象  这个函数就是拷贝赋值函数
 * 类的拷贝赋值函数和类的缺省拷贝构造函数一样 也是浅拷贝 如果类中有指针类型的成员变量 则必须定义一个支持深拷贝的拷贝赋值函数
 *  
 *  语法  
 *  	类名& operator=(const 类名& that){
 *  		if(&that != this){
 *  			//释放内存
 *  			delete 成员变量
 *				//分配新内存
 *				new 成员变量
 *				//赋值新数据
 *				.....
 *  		}
 *  		return *this;//返回自引用
 *  	} 
 * */

#include <iostream>
#include <cstring>
using namespace std;


//先写一个简单 带又拷贝构造和拷贝赋值的类
class Integer{
public:
	Integer(int data=0):m_data(new int(data)){}
	//拷贝构造
	Integer(const Integer& that):m_data(new int(*that.m_data)){
		cout << "调用拷贝构造" << endl;
	}
	//拷贝赋值
	Integer& operator=(const Integer& that){
		cout << "调用拷贝赋值" << endl;
		if(&that != this){ //防止自赋值		
			//释放旧内存
			delete m_data;
			//申请新内存
			m_data = new int;
			//完成拷贝
			*m_data = *that.m_data;
		}
		return *this;//反回自引用
	}

	~Integer(void){
		delete m_data;
	}
	void showData(void){
		cout << *m_data << endl;
	}
private:
	int* m_data;
};

//再写一个字符串拷贝赋值和拷贝构造类
class String{
public:
	//构造函数
	String(const char* str):m_str(strcpy(new char(strlen(str)+1),str)){};
	//拷贝构造函数
	String(const String& that):m_str(strcpy(new char(strlen(that.m_str)+1),that.m_str)){}
	//拷贝赋值函数
	String& operator=(const String& that){
		if(&that != this){
			delete[] m_str;
			m_str = new char[strlen(that.m_str)];
			strcpy(m_str,that.m_str);
		}
		return *this;
	}
	
	void printStr(void){
		cout << m_str << endl;
	}

	~String(void){
		delete[] m_str;
	}
private:
	//用一个指针变量维护一个字符串
	char * m_str;
};

int main ()
{
	Integer i1=100;
	Integer i2=i1;  //i2(i1)  调用拷贝构造
	i2.showData();
	Integer i3;//定义
	i3 = i2;//这时候没有新的对象产生  =号属于赋值操作
	i3.showData();

	String s1="hello c++";
	String s2(s1);//拷贝构造函数
	s2.printStr();
	String s3("hello world");
	s3=s2;
	s3.printStr();

	return 0;
}
