#include "Duck.h"

class MallardDuck : public Duck
{
protected:
	int tmp;
	void StepY(int s)
	{		
		this->posY += s;
	}
public:
	MallardDuck(void);
	~MallardDuck(void);

	void Fly()
	{
		StepX(3);
		StepY(4);

		Draw();
	}
};