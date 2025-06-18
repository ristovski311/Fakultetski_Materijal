#pragma once

#include <iostream>
using namespace std;

class Vozilo
{
	double sopTez;                                      // Sopstvena tezina.

public:

	Vozilo(double st) { sopTez = st; }                 // Konstruktor.
	virtual char vrsta() const = 0;                     // Vrsta vozila.
	virtual double tezina() const { return sopTez; }   // Ukupna tezina.

protected:

	virtual void pisi(ostream& d) const                // Pisanje.
	{
		d << vrsta() << ' (' << sopTez << ',';
	}

	friend ostream& operator<< (ostream& d, const Vozilo& v)
	{
		v.pisi(d);
		return d;
	}
};