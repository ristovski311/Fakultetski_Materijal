#pragma once
#include <iostream>
#include "Kreator.h"
#include "X.h";
using namespace std;

void main()
{
	// X *tmp = new X();

	Kreator *k = new Kreator();
	X obj = k->KreirajObjekatX();
	obj.Prikaz();

	X obj1 = k->KreirajObjekatX();
	obj1.Prikaz();

	k->PrikaziBroj();
	cout << *k;
}

