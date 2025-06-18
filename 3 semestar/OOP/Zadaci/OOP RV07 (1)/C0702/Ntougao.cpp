#include "Ntougao.h"

Ntougao::Ntougao(int n)
{
	br_temena = n;
	duzina = new float[n];
}

Ntougao::~Ntougao()
{
	delete[] duzina;
}

float Ntougao::Obim()
{
	float o = 0;
	for (int i = 0; i < br_temena; i++)
		o += duzina[i];
	return o;
}

istream& operator>>(istream& in, Ntougao& nt)
{
	for (int i = 0; i < nt.br_temena; i++)
		in >> nt.duzina[i];
	return in;
}