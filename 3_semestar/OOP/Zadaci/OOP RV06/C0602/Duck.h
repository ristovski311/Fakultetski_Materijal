#include <iostream>
#include <math.h>

using namespace std;

class Duck
{
	int id;
	int power;

protected:
	int posX;
	int posY;

	void StepX(int s)
	{
		posX += s;
	}

public:
	static int TotalCount;
	static int ActiveCount;

	Duck(void);

	virtual ~Duck(void);

	void Draw()
	{
		cout << id << " at " << posX << ", " << posY << endl;
	}

	void Swim()
	{
		srand(TotalCount % id);
		int s = rand();

		StepX(s);
		Draw();
	}

	void Quack()
	{
		cout << endl << "Quack!" << endl << endl;
	}
};