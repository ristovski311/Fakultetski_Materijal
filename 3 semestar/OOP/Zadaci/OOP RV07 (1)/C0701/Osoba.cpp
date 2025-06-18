#include "Osoba.h"

void Osoba::citaj() 
{
	cout << "Ime i prezime?     ";
	getline(cin, ime);
	cout << "Datum rodjenja?    ";
	getline(cin, datum);
	cout << "Adresa stanovanja? ";
	getline(cin, adresa);
}

void Osoba::pisi() const 
{
	cout << "Ime i prezime:     " << ime << endl;
	cout << "Datum rodjenja:    " << datum << endl;
	cout << "Adresa stanovanja: " << adresa << endl;
}