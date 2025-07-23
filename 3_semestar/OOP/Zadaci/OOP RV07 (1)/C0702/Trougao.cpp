#include "Trougao.h"
#include<math.h>

Trougao::Trougao()
	:Ntougao(3)
{}

Trougao::~Trougao()
{}

float Trougao::Povrsina()
{
	float p;
	float a = duzina[0];
	float b = duzina[1];
	float c = duzina[2];
	float s = (a + b + c) / 2;
	p = sqrt(s*(s - a)*(s - b)*(s - c));

	return p;
}