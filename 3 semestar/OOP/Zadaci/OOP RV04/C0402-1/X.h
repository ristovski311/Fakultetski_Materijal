#pragma once
#include <iostream>
using namespace std;

class X
{
private:
	int pom;
	X()
	{
		pom = -1;
	}

	friend class Kreator;
public:
	void Prikaz()
	{
		cout << pom << endl;
	}
	int VratiPom()
	{
		return pom;
	}
};