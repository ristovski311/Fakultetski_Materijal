#include "Zaposlen.h"

void Zaposlen::citaj() 
{
	Osoba::citaj();
	cout << "Naziv firme?       ";
	getline(cin, firma);
	cout << "Naziv odeljenja?   ";
	getline(cin, odeljenje);
}

void Zaposlen::pisi() const 
{
	Osoba::pisi();
	cout << "Naziv firme:       " << firma << endl;
	cout << "Naziv odeljenja:   " << odeljenje << endl;
}