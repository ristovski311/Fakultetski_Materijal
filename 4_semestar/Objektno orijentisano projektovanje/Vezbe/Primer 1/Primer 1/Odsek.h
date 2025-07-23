#pragma once
#include "Student.h"
#include "Predmet.h"
class Student;

class Odsek
{
private:
	char* naziv;
	Student** studenti;
	int maxBrStudenata;
	int trBrStudenata;
public:
	Odsek(const char* naziv, int maxBrStudenata);
	virtual ~Odsek();
	bool DodajStudenta(Student* s);
	char* Naziv();
	void Prikaz();
};
