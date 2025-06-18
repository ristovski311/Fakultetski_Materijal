// Ovo je pomocna klasa koja opisuje jedan cvor liste
// (jedan objekat ove klase bice jedan cvor).
//
// U klaci Stack ce atribut koji cuva glavu liste
// biti tipa CvorListe.
//
// Nase je pravo da isprojektujemo pomocnu klasu
// ukoliko nam je potrebna.

package kolekcija;

class CvorListe {
	
	Object info;
	CvorListe next;
	
	CvorListe (Object o, CvorListe n)
	{
		info = o;
		next = n;
	}

}
