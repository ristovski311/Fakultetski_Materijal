import matematika.*;

class Glavna {
	
	public static void main (String[] args)
	{
		Funkcija linf, kvadf;
		
		linf  = new LinearnaFunkcija(1.1, 2.2);
		kvadf = new KvadratnaFunkcija(1.1, 2.2, -2);
		
		if (linf.imaRealneNule())
		{
			double[] pom;
			pom = linf.nule();
			System.out.println("Nula linearne: " + pom[0]);
		}
		else System.out.println("Linearna funkcija nema realne nule.");
		
		if (kvadf.imaRealneNule())
		{
			double[] pom;
			pom = kvadf.nule();
			System.out.println("Nule kvadratne: " + pom[0] + " i " + pom[1]);
		}
		else System.out.println("Kvadratna funkcija nema realne nule.");
		
	}

}

// Eksperimentisati!
// Kreirati linearnu funkciju sa argumentima (1.1, 0) i videti sta se dogadja.
// Kreirati kvadratnu funkciju sa argumentima (0, 1.1, -2) i videti sta se dogadja.
