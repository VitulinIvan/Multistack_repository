#include <iostream>
#include "Stack.h"
#include "Multistack.h"

int main()
{
	TMultiStack<int>a(9, 3);
	a.Push(1, 0);
	a.Push(2, 0);
	a.Push(3, 1);
	a.Push(4, 1);
	a.Push(5, 2);
	a.Push(6, 0);
	a.Push(7, 0);
	cout << a;
	a.Push(8, 0);
	cout << a;
	a.Push(9, 0);
	cout << a;
	return 0;
}