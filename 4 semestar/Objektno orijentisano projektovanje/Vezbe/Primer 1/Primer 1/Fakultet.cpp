#include "Fakultet.h"
#include <string.h>
#include <iostream>
using namespace std;

Fakultet* Fakultet::instanca;

Fakultet::Fakultet()
{

}

Odsek* Fakultet::PronadjiOdsek(const char* naziv)
{
	for (int i = 0; i < trBrOdseka; i++)
		if (!strcmp(odseci[i]->Naziv(), naziv))
			return odseci[i];

	return nullptr;
}

Fakultet* Fakultet::GetInstanca()
{
	if (instanca == nullptr)
		instanca = new Fakultet();

	return instanca;
}

bool Fakultet::UpisiStudenta(Student* s, const char* naziv)
{
	Odsek* o = PronadjiOdsek(naziv);
	if (o != nullptr && o->DodajStudenta(s))
	{
		s->UpisiNaOdsek(o);
		return true;
	}
	return false;
}

void Fakultet::PostaviParametre(const char* naziv,
	const char* datumOsnivanja, int maxBrOdseka)
{
	this->naziv = new char[strlen(naziv) + 1];
	strcpy(this->naziv, naziv);
	strcpy(this->datumOsnivanja, datumOsnivanja);
	this->maxBrOdseka = maxBrOdseka;
	this->trBrOdseka = 0;
	odseci = new Odsek * [maxBrOdseka];
}

void Fakultet::DodajOdsek(Odsek* o)
{
	if (this->odseci != nullptr && trBrOdseka < maxBrOdseka)
		odseci[trBrOdseka++] = o;
}

Fakultet::~Fakultet()
{
	delete[] naziv;

	for (int i = 0; i < trBrOdseka; i++)
		delete odseci[i];
	delete[] odseci;
}

void Fakultet::Prikaz()
{
	cout << naziv << " osnovan " << datumOsnivanja << " ima " << trBrOdseka 
		<< " odseka:" << endl << endl;
	for (int i = 0; i < trBrOdseka; i++)
		odseci[i]->Prikaz();
}
