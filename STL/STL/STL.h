#ifndef _STL_H
#define _STL_H

template <class T>

class A
{
public:
	A(){};
	~A(){};
	A(const A &);
	A operator=(const A&);
	T Get(T a,T b)
	{
		T c;
		c = a + b;
		return c;
	}
private:
	T m_nT;
};

// template <class  T> 
// class   Foo   { 
// public: 
// 	Foo(); 
// 	void   someMethod(T   x); 
// private: 
// 	T   b; 
// }; 


#endif