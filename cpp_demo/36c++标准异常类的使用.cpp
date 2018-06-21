/*
 * c++标准异常类的使用
 * 场景：程序执行过程中可能抛出多种异常，都写catch捕获比较繁琐。所以使用标准异常类派生自己的异常类，在捕获的时候异常类型写
 * 标准类的引用。这样就形成了多态的环境 引用子类对象的基类引用。通过重新标准异常类中的what函数，来处理派生异常类中的异常。
 *
 * 标准异常类简写
 * class exception{
 * public:
 * 		exception(void)throw(){} //构造函数
 *		virtual ~exception(void)throw(){}//析构函数，派生类也要加
 *		virtual const char* what()const throw(){}//派生类重写
 * };
 *
 * */

#include <iostream>
using namespace std;

class ErrorA:public exception{
public:
	ErrorA(void)throw(){

	}
	~ErrorA(void)throw(){ //一定要加，防止放松throw导致编译错误
	
	}
	//重写异常处理
	const char* what()const throw(){
		return "文件错误";
	}
};

int main()
{
	try{
		//...前面是写的代码流程 如果碰到错误 直接抛出来
		throw ErrorA();
	}
	catch(exception& ex){
		cout << ex.what() << endl;//多态，这样就调用到了派生类的异常处理
	}
	return 0;
}
