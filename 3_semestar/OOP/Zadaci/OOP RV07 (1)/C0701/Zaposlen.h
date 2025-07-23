#pragma once
#include "Osoba.h"

class Zaposlen : public Osoba
{
	string firma, odeljenje;

public:
	Zaposlen()
		: Osoba()
	{

	}

	void citaj();
	void pisi() const;
};