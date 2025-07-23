#pragma once
#include "Osoba.h"

class Djak : public Osoba
{
	string skola, razred;

public:
	Djak()
		: Osoba()
	{

	}

	void citaj();
	void pisi() const;
};