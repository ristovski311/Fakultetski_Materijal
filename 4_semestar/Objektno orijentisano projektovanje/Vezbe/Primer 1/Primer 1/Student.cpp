#include "Student.h"
#include <string.h>
#include <iostream>
using namespace std;

Predmet* Student::NadjiPredmet(const char* p)
{
	for (int i = 0; i < trBrPredmeta; i++)
		if (!strcmp(predmeti[i]->Naziv(), p))
			return predmeti[i];

	return nullptr;
}

Student::Student(int brojIndeksa, const char* ime, const char* prezime,
	const char* jmbg, const char* datumUpisa, int max)
{
	this->brojIndeksa = brojIndeksa;

	this->ime = new char[strlen(ime) + 1];
	strcpy(this->ime, ime);

	this->prezime = new char[strlen(prezime) + 1];
	strcpy(this->prezime, prezime);

	strcpy(this->jmbg, jmbg);
	strcpy(this->datumUpisa, datumUpisa);

	this->predmeti = new Predmet * [max];
	this->maxBrPredmeta = max;
	this->trBrPredmeta = 0;
}

Student::~Student()
{
	//delete this->odsek;
	//for (int i = 0; i < trBrPredmeta; i++)
	//{
	//	delete predmeti[i];
	//}
	delete[] predmeti;

	delete[] ime;
	delete[] prezime;
}

void Student::DodajPredmet(Predmet* predmet)
{
	if (trBrPredmeta < maxBrPredmeta)
		predmeti[trBrPredmeta++] = predmet;
}

void Student::IzbaciPredmet(Predmet* predmet)
{
	int i = 0;
	while (i < trBrPredmeta && predmeti[i] != predmet)
		i++;

	for (int j = i; j < trBrPredmeta - 1; j++)
		predmeti[j] = predmeti[j + 1];

	trBrPredmeta--;
}

void Student::UpisiNaOdsek(Odsek* odsek)
{
	this->odsek = odsek;
}

void Student::Prikaz()
{
	cout << brojIndeksa << " " << ime << " " << prezime << " " << jmbg 
		<< " upisan " << datumUpisa	<< " na odseku " << odsek->Naziv() 
		<< " slusa " << trBrPredmeta << " predmeta: "<<endl;

	for (int i = 0; i < trBrPredmeta; i++)
		predmeti[i]->Prikaz();

	cout << endl;
}

int Student::PoloziPredmete(char** nazivi, int n)
{
	int s = 0;
	Predmet* p;
	for(int i = 0; i < n; i++)
	{
		p = NadjiPredmet(nazivi[i]);
		if (p != nullptr)
			s += p->GetESPB();
	}

	return s;
}
