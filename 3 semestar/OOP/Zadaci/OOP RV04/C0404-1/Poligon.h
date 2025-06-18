#include "Tacka.h"
class Poligon
{
	int n; //broj temena
	Tacka* niz;

public:
	Poligon();
	Poligon(int x);
	~Poligon();
	Poligon(const Poligon& w);

	int vratiBrojTemena()
	{
		return n;
	}

	Poligon& operator=(const Poligon& v);
	Poligon& operator+(const Poligon& v);

	void obim();
	void ucitaj();
	void prikazi();

	void kopiraj(const Poligon& w);
	void kopirajSegment(int startIndex, const Poligon& w, int startWIndex, int krajWIndex);
	void obrisi();
	void zauzmi(int dim);
};