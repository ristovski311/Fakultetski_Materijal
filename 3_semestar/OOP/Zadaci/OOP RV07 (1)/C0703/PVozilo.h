#pragma once
#include "Vozilo.h"

class PVozilo : public Vozilo
{
	double srTez;                             // Srednja tezina putnika.
	int brPut;                                // Broj putnika.

public:
	PVozilo(double st, double srt, int bp) // Konstruktor.
		: Vozilo(st)
	{
		srTez = srt;
		brPut = bp;
	}

	char vrsta() const  // Vrsta vozila.
	{
		return 'P';
	}

	double tezina() const                                // Ukupna tezina.
	{
		return Vozilo::tezina() + srTez * brPut;
	}

private:
	void pisi(ostream& d) const                          // Pisanje.
	{
		Vozilo::pisi(d);
		d << srTez << ', ' << brPut << ')';
	}
};