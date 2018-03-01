#include "Deque.h"

int main()
{
	Sequence *s1 = new stack();
	Sequence *s2 = new Queue();

	s1->push(1);
	s2->push(1);

	s1->pop();
	s2->pop();

	delete s1;
	delete s2;

	getchar();
	return 0;
}