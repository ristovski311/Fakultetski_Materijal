#include "Matrica.h"
#include <iostream>
using namespace std;

Matrica::Matrica()
{
	m = n = 0;
	a = 0;
}

Matrica::Matrica(int brVrsta, int brKolona)
	: n(brVrsta), m(brKolona)
{
	a = new int* [n];

	for (int i = 0; i < n; i++)
		a[i] = new int[m];
}

Matrica::Matrica(const Matrica& mat)
	: n(mat.n), m(mat.m)
{
	a = new int* [n];

	for (int i = 0; i < n; i++)
		a[i] = new int[m];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			a[i][j] = mat.a[i][j];
}

Matrica::~Matrica()
{
	if (a != 0)
	{
		for (int i = 0; i < n; i++)
			delete[] a[i];

		delete[] a;
	}
}

istream& operator>>(istream& ulaz, Matrica& v)
{
	for (int i = 0; i < v.n; i++)
		for (int j = 0; j < v.m; j++)
			ulaz >> v.a[i][j];

	return ulaz;
}

ostream& operator<<(ostream& izlaz, const Matrica& v)
{
	for (int i = 0; i < v.n; i++)
	{
		for (int j = 0; j < v.m; j++)
			izlaz << v.a[i][j] << " ";

		izlaz << endl;
	}
	return izlaz;
}

Matrica Matrica::pomnozi(const Matrica& mat)
{
	if (m == mat.n)
	{
		Matrica rezultat(n, mat.m);

		for (int i = 0; i < rezultat.n; i++)
		{
			for (int j = 0; j < rezultat.m; j++)
			{
				rezultat.a[i][j] = 0;
				for (int l = 0; l < m; l++)
					rezultat.a[i][j] += a[i][l] * mat.a[l][j];
			}
		}

		return rezultat;
	}

	cout << "Matrice se ne mogu pomnoziti" << endl;

	Matrica r;
	return r;
}