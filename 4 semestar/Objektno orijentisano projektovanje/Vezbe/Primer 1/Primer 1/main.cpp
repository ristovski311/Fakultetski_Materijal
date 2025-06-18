#pragma once
#include "Fakultet.h"
#include<iostream>
using namespace std;

void main()
{
	Fakultet* f = Fakultet::GetInstanca();
	f->PostaviParametre("Elfak", "01.10.1960.", 10);

	f->DodajOdsek(new Odsek("RII", 1000));
	f->DodajOdsek(new Odsek("EKM", 700));
	f->DodajOdsek(new Odsek("US", 900));

	Student* s1 = new Student(19858, "Marko", "Maric", "0704003730112", "01.10.2023.", 30);
	Student* s2 = new Student(19859, "Nikola", "Jovanovic", "0510003730003", "01.10.2023.", 30);
	Student* s3 = new Student(19860, "Ana", "Djordjevic", "1704003735012", "01.10.2023.", 30);
	Student* s4 = new Student(19861, "Branka", "Ilic", "0912003735005", "01.10.2023.", 30);
	Student* s5 = new Student(19862, "Milica", "Aleksic", "2210003735002", "01.10.2023.", 30);

	f->UpisiStudenta(s1, "RII");
	f->UpisiStudenta(s2, "EKM");
	f->UpisiStudenta(s3, "US");
	f->UpisiStudenta(s4, "US");
	f->UpisiStudenta(s5, "RII");

	Predmet* p1 = new Predmet("OOProj", 6);
	Predmet* p2 = new Predmet("OOP", 5);
	Predmet* p3 = new Predmet("Komponente", 6);
	Predmet* p4 = new Predmet("Osnove US", 3);

	s1->DodajPredmet(p1);
	s1->DodajPredmet(p2);
	s1->DodajPredmet(p3);
	s1->IzbaciPredmet(p3);

	s2->DodajPredmet(p4);
	s2->DodajPredmet(p1);
	
	s3->DodajPredmet(p2);
	s3->DodajPredmet(p4);

	s4->DodajPredmet(p1);
	
	s5->DodajPredmet(p3);

	f->Prikaz();

	cout << "*************************************************************" << endl;
	cout << "Polozeni predmeti: " << endl;
	p1->Prikaz();
	p2->Prikaz();
	cout << "Za studenta " << endl;
	s1->Prikaz();

	char** niz = new char* [2];
	niz[0] = new char [strlen(p1->Naziv()) + 1];
	strcpy(niz[0], p1->Naziv());
	niz[1] = new char [strlen(p2->Naziv()) + 1];
	strcpy(niz[1], p2->Naziv());

	cout << "ESPB = " << s1->PoloziPredmete(niz,2) << endl;
	
	delete niz[0];
	delete niz[1];
	delete[]niz;

	delete f;
	
	delete p1;
	delete p2;
	delete p3;
	delete p4;

	delete s1;
	delete s2;
	delete s3;
	delete s4;
	delete s5;
}