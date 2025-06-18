#pragma once
class Predmet
{
private:
	char* naziv;
	int brojEspb;
public:
	Predmet(const char* naziv, int espb);
	virtual ~Predmet();
	int GetESPB();
	char* Naziv();
	void Prikaz();
};