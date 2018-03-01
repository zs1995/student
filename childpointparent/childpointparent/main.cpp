// #include <iostream>   
// using namespace std;   
// class A   
// {   
// public:   
// 	virtual void foo()   
// 	{   
// 		cout << "A's foo()" << endl;   
// 		//bar();   
// 	}   
// 	/*virtual*/ void bar()   
// 	{   
// 		cout << "A's bar()" << endl;   
// 	}   
// };   
// class B: public A   
// {   
// public:   
// 	virtual void foo()   
// 	{   
// 		cout << "B's foo()" << endl;   
// 		//A::foo();   
// 	}   
// 	void bar()   
// 	{   
// 		cout << "B's bar()" << endl;   
// 	}   
// };   
// int main()   
// {   
// 	B bobj;   
// 	A *aptr = &bobj;   
// 	aptr->bar();   
// 	A aobj = *aptr; //转化为A类对象  
// 	aobj.foo(); 
// 	//aobj.bar();
// 
// 	A aobjtmp;
// 	B *bptr = (B*)&aobjtmp;
// 	bptr->foo();
// 	B bobjtmp = *bptr;
// 	bobjtmp.bar();
// 
// 	getchar();
// }

#include <iostream>
using namespace std;
int func(int n,int m)
{
	printf("n:%d,m:%d\n",n,m);
	return m+n;
}

int main()
{
	int a =1;
	int n = func(a++,a++);
	//printf("%d\n",n);
	cout << n <<endl;
    int b = 1;
	int m = func(++b,++b);
	//cout << m <<endl;
	
	printf("%d\n",m);
	getchar();
	return 0;
}