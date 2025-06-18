#include "Odsek.h"
#include <string.h>
#include <iostream>
using namespace std;

Odsek::Odsek(const char* naziv, int maxBrStudenata)
{
	this->naziv = new char[strlen(naziv) + 1];
	strcpy(this->naziv, naziv);

	this->maxBrStudenata = maxBrStudenata;
	this->studenti = new Student * [maxBrStudenata];

	trBrStudenata = 0;
}

Odsek::~Odsek()
{
	delete[] naziv;

	//for (int i = 0; i < trBrStudenata; i++)
	//	delete studenti[i];
	delete[] studenti;
}

bool Odsek::DodajStudenta(Student* s)
{
	if (trBrStudenata < maxBrStudenata)
	{
		studenti[trBrStudenata++] = s;
		return true;
	}

	return false;
}


char* Odsek::Naziv()
{
	return naziv;
}

void Odsek::Prikaz()
{
	cout << "*****Odsek " << naziv << " ima " << trBrStudenata << " studenta:" << endl;
	for (int i = 0; i < trBrStudenata; i++)
		studenti[i]->Prikaz();

	cout << endl;
}
