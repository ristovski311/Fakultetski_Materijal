#include"ChainedScatterTable.h"

void main()
{
	ChainedScatterTable tablica(64);
	ChainedScatterObject o("2907982750051", "Nikola Davidovic");
	tablica.insert(o);
	ChainedScatterObject o1("2706985730058", "Pera Peric");
	ChainedScatterObject o2("2907982750051", "Nikola Davidovic");
	ChainedScatterObject o3("2907982750251", "Pera");
	tablica.insert(o3);
	tablica.insert(o2);
	tablica.print();
	tablica.insert(o2);
	tablica.print();
	tablica.insert(o1);
	tablica.print();
	tablica.insert(o1);
	tablica.print();
	tablica.insert(o2);
	tablica.insert(o3);
	tablica.insert(o3);
	tablica.print();
}