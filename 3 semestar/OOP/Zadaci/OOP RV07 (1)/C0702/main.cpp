#include "Trougao.h"
using namespace std;

void F1(Trougao& t)
{
	cout << t.Obim() << endl;
}

void main()
{
	//ntougao n; 
	//ntougao* s = new ntougao();

	Ntougao* p;

	p = new Trougao;

	cout << "unesite duzine stranica " << endl;

	cin >> *p;

	cout << "obim: " << p->Obim() << endl;

	cout << "povrsina: " << p->Povrsina() << endl;


	Trougao t1;
	cout << "unesite stranice trougla" << endl;
	cin >> t1;
	F1(t1);

	t1.Obim();
	t1.Ntougao::Obim();

	Ntougao& nt = t1;
	cout << "obim: " << nt.Obim() << endl;
	cout << "povrsina: " << nt.Povrsina() << endl;

	delete p;
}