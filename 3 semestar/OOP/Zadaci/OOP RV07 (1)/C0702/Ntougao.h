#include <iostream>
using namespace std;

class Ntougao
{
protected:
	int br_temena;
	float *duzina;
public:
	virtual float Povrsina() = 0;
	float Obim();
	Ntougao(int n);
	virtual ~Ntougao();
	friend istream& operator>>(istream& in, Ntougao& nt);
};