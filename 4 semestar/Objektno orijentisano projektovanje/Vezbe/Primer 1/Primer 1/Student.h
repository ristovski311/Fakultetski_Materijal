#pragma once
#include "Odsek.h"
#include "Predmet.h"
class Odsek;

class Student
{
private:
	int brojIndeksa;
	char* ime;
	char* prezime;
	char jmbg[14];
	char datumUpisa[12];
	Odsek* odsek;
	Predmet** predmeti;
	int maxBrPredmeta;
	int trBrPredmeta; 
	Predmet* NadjiPredmet(const char* p);
public:
	Student(int brojIndeksa, const char* ime, const char* prezime,
		const char* jmbg, const char* datumUpisa, int max);
	virtual ~Student();
	void DodajPredmet(Predmet* predmet);
	void IzbaciPredmet(Predmet* predmet);
	void UpisiNaOdsek(Odsek* odsek);
	void Prikaz();
	int PoloziPredmete(char** nazivi, int n);
};
