#include "Ntougao.h"

class Trougao : public Ntougao
{
public:
	Trougao();
	virtual ~Trougao();
	virtual float Povrsina();

	float Obim()
	{
		float o = 0;
		for (int i = 0; i < br_temena; i++)
			o -= duzina[i];
		return o;
	}
};