#pragma once
#include <string>
#include <iostream>
using namespace std;

class Osoba
{
	string ime, datum, adresa;

public:
	Osoba() {}
	virtual void citaj();
	virtual void pisi() const;
};