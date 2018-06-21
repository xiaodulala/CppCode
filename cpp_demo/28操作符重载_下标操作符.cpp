/*
 * 下标运算符重载
 *  语义分析:
 *  a[0]==>a.operator[](0)
 *  表达式结果 如果左操作数对象为左值，表达式结果为左值。如果左操作数为常对象右值，表达式结果为右值。
 *  但是一个函数会无法返回即是左值，也是右值的结果。所以需要写两个版本，一个常函数和一个非常函数。可以形成重载
 *  右操作是即可以是左值 也可以是右值。
 * */


#include <iostream>
using namespace std;
class Array{
public:
	Array(size_t size):m_data(new int[size]),m_size(size){}
	~Array(void){
		delete[] m_data;
		m_data = NULL;
	}
	//重载[] 非常函数 非常对象调用 返回左值。
	int& operator[](const size_t i){
		return m_data[i];
	}
	//重在[] 常函数  常对象调用 返回右值
	//基本类型返回右值 不需要加const修饰了 就是一个将亡右值
	int operator[](const size_t i)const{
		return m_data[i];
	}
private:
	int *m_data;//指向一块内存地址
	size_t m_size;
};


int main (){
	Array a(10);
	for(int i=0;i<10;i++){
		a[i]=i+1;
		cout << a[i] << " ";
	}
	const Array& ra = a;
	cout << ra[5] << endl;
	cout << endl;

}
