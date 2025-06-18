#include "Derived.h"
using namespace std;

int main()
{
	//Base* a = new Base(10);

	Derived d;
	d.NameOf();
	d.InvokingClass();

	Base f(d);

	Base& cc = d;
	cc.NameOf();
	cc.InvokingClass();
	d.NameOf();
	cout << "!!!!!" << endl;

	Derived c(11, 12);
	Derived *a = &c;
	Base *b = &c;

	b->NameOf();        // Poziv virtualne f-je
	b->InvokingClass(); // Poziv ne-virtualne f-je
	a->NameOf();        // Poziv virtualne f-je
	a->InvokingClass(); // Poziv ne-virtualne f-je
	a->Base::NameOf();  // eksplicitni poziv f-je iz roditeljske klase

	Derived* bb = new Derived(10, 10);
	Base* ab = bb;
	bb->NameOf();
	ab->NameOf();
	bb->InvokingClass();
	ab->InvokingClass();
	delete ab;
	bb->NameOf();

}