#pragma once
#include "Vozilo.h"

class TVozilo : public Vozilo
{
	double teret;                                       // Tezina tereta.

public:
	TVozilo(double st, double t)  // Konstruktor.
		: Vozilo(st)
	{
		teret = t;
	}

	char vrsta() const  // Vrsta vozila.
	{
		return 'T';
	}

	double tezina() const                              // Ukupna tezina.
	{
		return Vozilo::tezina() + teret;
	}

private:
	void pisi(ostream& d) const                        // Pisanje.
	{
		Vozilo::pisi(d);
		d << teret << ')';
	}
};