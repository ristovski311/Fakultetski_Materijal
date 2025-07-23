#include "Poligon.h"
#include <math.h>
#include <iostream>
using namespace std;

Poligon::Poligon()
{
	n = 0;
	niz = 0;
}

Poligon::Poligon(int x)
{
	zauzmi(x);
}

void Poligon::zauzmi(int dim)
{
	n = dim;
	this->niz = new Tacka[n];
}

Poligon::~Poligon()
{
	obrisi();
}

void Poligon::obrisi()
{
	if (niz != 0)
	{
		delete[] niz;
		niz = 0;
	}

}

Poligon::Poligon(const Poligon& w)
{
	this->kopiraj(w);
}

void Poligon::kopiraj(const Poligon& w)
{
	zauzmi(w.n);
	kopirajSegment(0, w, 0, n);

}

void Poligon::kopirajSegment(int startIndex,
	const Poligon& w,
	int wStartIndex,
	int wKrajIndex)
{
	int brojac = startIndex;
	int index = wStartIndex;

	while (index < wKrajIndex
		&& brojac < this->n)
	{
		niz[brojac] = w.niz[index];
		brojac++;
		index++;
	}
}

Poligon& Poligon::operator=(const Poligon& v)
{
	if (this != &v)
	{
		obrisi();
		kopiraj(v);
	}
	return *this;
}

Poligon& Poligon::operator+(const Poligon& v)
{
	Poligon* rezultat = new Poligon;		// !!!!!!!!!!!!!!!!!!!!!!!
	rezultat->zauzmi(this->n + v.n);
	rezultat->kopirajSegment(0, *this, 0, n);
	rezultat->kopirajSegment(n, v, 0, v.n);

	return *rezultat;
}

void Poligon::obim()
{
	double s;
	s = 0;
	s += sqrt((double)(niz[0].GetX() - niz[n - 1].GetX()) * (niz[0].GetX() - niz[n - 1].GetX())
		+ (niz[0].GetY() - niz[n - 1].GetY()) * (niz[0].GetY() - niz[n - 1].GetY()));

	for (int i = 0; i < n - 1; i++)
	{
		double segment = sqrt((double)(niz[i + 1].GetX() - niz[i].GetX()) * (niz[i + 1].GetX() - niz[i].GetX())
			+ (niz[i + 1].GetY() - niz[i].GetY()) * (niz[i + 1].GetY() - niz[i].GetY()));
		cout << segment << endl;
		s += segment;
	}

	cout << s << endl;
}

void Poligon::ucitaj()
{
	if (n > 0)
	{
		int xx, yy;
		for (int i = 0; i < n; i++)
		{
			cin >> xx >> yy;
			niz[i].SetX(xx);
			niz[i].SetY(yy);

		}
	}
}

void Poligon::prikazi()
{
	if (n > 0)
	{
		for (int i = 0; i < n; i++)
			cout << niz[i].GetX() << ", " << niz[i].GetY() << endl;
	}

	cout << endl;
}