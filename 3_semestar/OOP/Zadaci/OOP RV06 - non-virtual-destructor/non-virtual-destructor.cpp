#include<iostream> 

using namespace std;

class base {
public:
	base()
	{
		cout << "Constructing base \n";
	}

	/*virtual*/ ~base()
	{
		cout << "Destructing base \n";
	}
};

class derived : public base {
public:
	derived()
	{
		cout << "Constructing derived \n";
	}
	~derived()
	{
		cout << "Destructing derived \n";
	}
};

int main(void)
{
	cout << "Object d1:" << endl;
	derived *d1 = new derived();
	base *b = d1;
	delete d1;

	cout << endl << endl << "Object d2:" << endl;
	derived *d2 = new derived();
	delete d2;

	getchar();
	return 0;
}