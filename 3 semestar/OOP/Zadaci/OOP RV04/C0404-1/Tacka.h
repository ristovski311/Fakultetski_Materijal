class Tacka
{
	int x;
	int y;

public:
	Tacka()
	{
		x = y = 0;
	}

	Tacka(int xx, int yy, int zz)
		:x(xx), y(yy)
	{
	}

	int GetX() { return x; }
	int GetY() { return y; }

	void SetX(int xx) { x = xx; }
	void SetY(int yy) { y = yy; }
};