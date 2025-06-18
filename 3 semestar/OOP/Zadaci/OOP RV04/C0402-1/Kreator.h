#pragma once
#include "X.h"
#include <iostream>
using namespace std;
class Kreator
{
private:
	int brojIstanciObjekataX;
public:
	Kreator()
		:brojIstanciObjekataX(0)
	{
		
	}

	X& KreirajObjekatX()
	{
		X *obj = new X();
		brojIstanciObjekataX++;
		obj->pom = brojIstanciObjekataX;

		return *obj;
	}

	void PrikaziBroj()
	{
		cout << "Broj Kreiranih istanci klase X je: " << brojIstanciObjekataX << endl;
	}

	friend ostream& operator<<(ostream& ulaz, const Kreator& k);
};

ostream& operator<<(ostream& ulaz, const Kreator& k)
{
	ulaz << "Primer prijatelhjske operatorske funkcije" << endl;
	ulaz << "Broj Kreiranih istanci klase X je: " << k.brojIstanciObjekataX << endl;
	return ulaz;
}