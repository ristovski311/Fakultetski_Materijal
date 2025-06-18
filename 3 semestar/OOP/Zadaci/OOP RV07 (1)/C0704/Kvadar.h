#pragma once

class Kvadar : public Predmet
{
	double a, b, c;

public:
	Kvadar(double ss = 1, double aa = 1, double bb = 1, double cc = 1) // Konstr.
		: Predmet(ss)
	{
		a = aa;
		b = bb;
		c = cc;
	}

	double V() const { return a * b * c; }                // Zapremina.

private:
	void Citaj(istream& dd)                               // Citanje.
	{
		Predmet::Citaj(dd);
		dd >> a >> b >> c;
	}

	void Pisi(ostream& dd) const {                       // Pisanje.
		dd << "kvadar[";
		Predmet::Pisi(dd);
		dd << ',' << a << ',' << b << ',' << c << ']';
	}
};