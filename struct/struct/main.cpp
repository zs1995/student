#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)
typedef struct A
{
	int b;
	double c;
	char d;
}n,*a;
#pragma pack()

typedef union X
{
	int y;
	double z;
	char u;
}x;

int main(int argc,char **argv)
{
	a m  = (struct A*)malloc(sizeof(struct A*));
	//memcpy(m,0,sizeof(m));
	m->b = 5;
	m->c = 9.0;
	printf("%d--%d\n",sizeof(n),m->b);
	printf("%d\n",sizeof(X));
	getchar();
	return 0;
}