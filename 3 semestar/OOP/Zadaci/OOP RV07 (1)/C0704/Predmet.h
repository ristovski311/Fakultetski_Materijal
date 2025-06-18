#pragma once
#include <iostream>
using namespace std;

class Predmet
{
	double sigma;	// Specificna tezina.

public:
	Predmet(double ss = 1) { sigma = ss; }		// Konstruktor.
	virtual double V() const = 0;				// Zapremina.
	double Q() const { return V() * sigma; }	// Tezina.

protected:
	virtual void Citaj(istream &dd) { dd >> sigma; }        // Citanje.
	virtual void Pisi(ostream &dd) const { dd << sigma; }   // Pisanje.

	friend istream& operator>> (istream& dd, Predmet &pp)   // Uopsteno citanje
	{
		pp.Citaj(dd);
		return dd;
	}

	friend ostream& operator<< (ostream& dd, const Predmet &pp) // pisanje.
	{
		pp.Pisi(dd);
		return dd;
	}
};