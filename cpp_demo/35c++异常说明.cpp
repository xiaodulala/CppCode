/*
 * c++异常说明
 * 1.在函数原型中增加异常说明，说明该函数可能抛出的异常类型。这里的函数 可以是普通函数，可以是成员函数，也可以是静态函数等。
 * 2.函数的异常说明是一种承诺，	表示该函数所抛出的异常类型不会超出说明的范围 但是如果抛出异常说明以外的类型，则该异常无法被正常捕获。
 * 	 而会被系统检测到，导致进程终止 eg1
 * 3.定义异常类的时候，两个异常类有可能是父子关系。这个时候，捕获异常的时候，要把子类的异常捕获写在前面，基类的异常捕获写到后面
 *   因为catch字句根据异常对象的类型自上而下顺序匹配，而不是最优匹配。如果子类的异常放到基类的后面进行捕获，前者将会被提前捕获
 *   为什么会提前捕获？由于向上造型的语法，向上造型编译器认为是安全的转换，可以显示转换。所以如果是子类异常对象，基类类型也可以捕获。
 *   而把子类放到前面，如果是子类异常，直接捕获。如果是基类异常，需要进行向下造型，向下造型是不安全的，需要显示转换。编译器不会自动转换
 *   所以不会被子类对象捕获。eg2
 * 4.异常说明的两种极端方式
 * 	  a.不写异常说明，表示可以抛出任何异常。
 * 	  b.空异常说明 throw() 表示不抛出任何异常。
 * 	  这里又个地方要注意：如果你继承别人的类写子类代码，在别人写的父类中有虚析构函数，并且带异常说明，你写的覆盖版本的析构函数，也要加
 * 	  异常说明
 * 5.在多文件编程中，函数的声明和定义分开的时候，要保持异常类型一致。
 * 	  声明 class A{ void func()throw(int); };
 *	  定义 void A::func(void)throw(int){...};
 * 6.如果基类中虚函数带有异常说明，那么该函数在子类的覆盖版本的异常说明，不能比基类中多，只能比基类中少或者一样。如果多了，将因为
 *  ”放松throw()限定“ 导致编译报错 eg3
 * */


#include <iostream>
using namespace std;



//eg1:定义两个异常类
class FileError{};
class MemoryError{};

void func(void)throw(FileError,MemoryError,int){
	//抛出异常说明之外的异常，不会被捕获。
	/*
	 * 相当于抛出一个int类型 会报出这样的错误:terminate called after throwing an instance of 'int' 
	 *
	 * 原因就是你抛出了一个在异常说明中没有的类型，但是为什么...的异常类型没有捕获到呢？ 注意...的异常类型，也是只捕获你在异常说明中
	 * 已经又的类型，只要你在异常说明中没有指定的异常类型，异常机制一律不会捕获。这样就会被系统捕获 而导致进程结束。
	 * 
	 * */
	throw -1;
	//抛出异常说明之内的异常 可以被捕获。
	throw MemoryError();
	throw FileError();
}


//eg2 带继承关系的异常类
class A{};
class B:public A{};

void func1(void)throw(A,B){
	/*
	 * 抛出子类对象异常
	 * */
	throw B();
}


//eg3 虚函数的异常说明
/*
 * func 又三个异常说明
 * func1可以抛出任何异常说明
 *  析构函数不抛出任何异常
 * */
class Base{
public:
	virtual void func(void)throw(FileError,MemoryError,int)=0;
	virtual void func1(void)=0;
	virtual ~Base(void)throw(){}	
};

/*
 * 
 * 注意 子类覆盖func的时候 异常只能比基类中的异常说明少。
 * 覆盖func1时候，可以抛出任何异常
 *
 * 注意 如果基类中又虚析构函数并且带有异常说明，并且显示的指出不抛出任意异常，这个时候子类中也要显示的写出析构函数不抛出任何异常。
 * 因为 如果子类中没有类类型的成员的时候，编译器会优化析构函数，就把析构函数去掉了。所以这个时候如果不显示写出来，编译器也不会报错。
 * 但是如果子类中有类类型的成员，如果你不显示的写出析构函数 编译会自己加一个默认的析构函数，但是默认加的析构函数是不会又异常说明的
 * 这个时候，再进行编译就会报错。 所以，基类中有这样的析构函数，在子类中一定要显示的指明。
 *
 * */

class Derive:public Base{
public:
	void func(void)throw(FileError){
		throw FileError();
	}
	void func1(void)throw(MemoryError,int){
		throw -1;
	}
	~Derive(void)throw(){}
private:
	A m_str;
};


int main ()
{
	try{
		func();
	}
	catch(FileError& ex){ //抛出的异常对象会在内存 ”安全区“保存。加引用是为了防止拷贝构造的发生。直接使用安全区的那个对象
		cout << "文件错误" << endl;
	}
	catch(MemoryError& ex){
		cout << "内存错误" << endl;
	}
	catch(...){
		/*
		 * 捕获其他类型，这里的其他类型 指的是你在异常说明中的类型，而前面没有用单独的catch捕获，会在这里捕获到。如果抛出的类型不在
		 * 函数的异常说明类型中。在这里也不捕获。比如函数抛出一个int类型，在异常说明里有，但是前面没有单独捕获，会在这里捕获。
		 * 如果异常说明没有int类型的异常，而你抛出了，在这里也不会把int类型当作其他类型捕获到！！
		 * 所以 在函数里千万不要抛出异常说明没有指定的类型。否则会导致系统捕获到而结束进程。
		 * */
		cout << "其他错误" << endl;//捕获其他类新的错误
	}

	

	/*
	 * eg2的异常捕获  先捕获基类类型，再不或子类类型.首先编译器会报出警告，错误被提前捕获。因为我抛出的B类型的错误，但是却被A类型的异常
	 * 进行向上构造后捕获到了，所以catch是按照异常类型顺序捕获的，而不是最优捕获。 这样写就是错误的
	 *
	 * 所以如果有父子类的异常对象时，要先捕获子类异常，再捕获基类异常。
	 *
	 * */
	try{
		func1();
	}
	/**
	 * 下面捕获方法错误。
	catch(A& ex){
		cout << "A类型异常" << endl;
	}
	catch(B& ex){
		cout << "B类型异常" << endl;
	}
	**/
	catch(B& ex){
		cout << "B类型异常" << endl;
	}
	catch(A& ex){
		cout << "A类型异常" << endl;
	}


	/*
	 * eg3
	 * */
	try{
		Derive d;
		d.func1();
	}
	catch(FileError& ex){
		cout << "文件错误" << endl;
	}
	catch(MemoryError& ex){
		cout << "内存错误" << endl;
	}
	catch(int ex){
		cout << "int类型错误" << endl;
	}



	return 0;
}
