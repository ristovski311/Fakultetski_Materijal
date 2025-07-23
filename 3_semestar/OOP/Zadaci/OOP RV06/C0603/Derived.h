#pragma once
#include <iostream>
#include "Base.h"

using namespace std;

class Derived : public Base
{
	int* vec;
public:
	void NameOf();
	void InvokingClass();

	Derived()
	{
		vec = 0;
	}

	Derived(int size1, int size2)
		: Base(size1)
	{
		vec = new int[size2];
	}

	~Derived()
	{
		if (vec != 0)
		{
			delete[] vec;
		}
	}
};