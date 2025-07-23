#pragma once
#include "predmet.h"

class Sfera : public Predmet
{
	double r;

public:
	Sfera(double ss = 1, double rr = 1)                       // Konstruktor.
		: Predmet(ss)
	{
		r = rr;
	}
	double V() const { return 4. / 3 * r*r*r * 3.14159; }    // Zapremina.

private:
	void Citaj(istream& dd)                                  // Citanje.
	{
		Predmet::Citaj(dd);
		dd >> r;
	}

	void Pisi(ostream& dd) const                             // Pisanje.
	{
		dd << "sfera [";
		Predmet::Pisi(dd);
		dd << ',' << r << ']';
	}
};