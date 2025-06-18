#include <iostream>
using namespace std;

const double PI = 3.1415926535897932;
 
class Valjak 
{
	double r, h;                              // Poluprecnik i visina.
public:
	Valjak(double rr = 1, double hh = 1)      // Inicijalizacija.
		:r(rr), h(hh)
	{
	}

	double R() const { return r; }                           // Poluprecnik.
	double H() const { return h; }                           // Visina.
	double V() const { return r * r * PI * h; }              // Zapremina.

	friend ostream& operator<<(ostream& izlaz, const Valjak& v) // Prikaz.
	{
		return izlaz << '[' << v.r << ',' << v.h << ']';
	}
};