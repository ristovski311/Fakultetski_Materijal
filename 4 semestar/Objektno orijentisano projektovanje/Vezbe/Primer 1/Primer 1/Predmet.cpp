#include "Predmet.h"
#include <string.h>
#include <iostream>
using namespace std;

Predmet::Predmet(const char* naziv, int espb)
{
	this->naziv = new char[strlen(naziv) + 1];
	strcpy(this->naziv, naziv);
	this->brojEspb = espb;
}

Predmet::~Predmet()
{
	delete[] naziv;
}

int Predmet::GetESPB()
{
	return brojEspb;
}

char* Predmet::Naziv()
{
	return naziv;
}

void Predmet::Prikaz()
{
	cout << naziv << " ESPB: " << brojEspb << endl;
}
