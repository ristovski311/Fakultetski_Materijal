#include "Djak.h"

void Djak::citaj() 
{
	Osoba::citaj();
	cout << "Naziv skole?       ";
	getline(cin, skola);
	cout << "Razred?            ";
	getline(cin, razred);
}

void Djak::pisi() const 
{
	Osoba::pisi();
	cout << "Naziv skole:       " << skola << endl;
	cout << "Razred:            " << razred << endl;
}