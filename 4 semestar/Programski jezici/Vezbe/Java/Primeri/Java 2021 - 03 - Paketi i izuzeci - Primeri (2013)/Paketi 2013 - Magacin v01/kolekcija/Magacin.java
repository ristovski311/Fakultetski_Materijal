package kolekcija;

public class Magacin {
	
	private CvorListe glava;	// Klasa Node je definisana dole.
	
//	Umetanje u lancanu listu:
	public void push (Object o)
	{
		glava = new CvorListe(o, glava);
	}
	
	public Object pop()
	{
		Object ob = null;
		if (glava != null)
		{
			ob = glava.info;
			glava = glava.next;
		}
		return ob;
	}
	
	public boolean prazanJe()
	{
		return glava==null;
	}
}