// klasa nije generička, a konstruktor jeste

public class Glavna
{
	public static void main(String args[])
	{
		NekaKlasa nk1 = new NekaKlasa("Blabla");
		
		NekaKlasa nk2 = new NekaKlasa(new Integer(10));
	}
}

// ne može se staviti dijamant nigde, ni pun ni prazan
// kod ovakve situacije
// inference only


