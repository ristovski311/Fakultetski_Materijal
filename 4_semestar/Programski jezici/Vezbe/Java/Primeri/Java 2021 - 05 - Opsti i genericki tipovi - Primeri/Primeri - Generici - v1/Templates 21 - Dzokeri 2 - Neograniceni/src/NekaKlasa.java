// Neograničeni džokeri

import java.util.*;	// za interfejs List i slično

public class NekaKlasa
{

	// šta ako metod traži argument tipa Lista<Object> ?
	// ovo deluje kao skroz univerzalna situacija
	// ali nije
	
	public static void štampajListuObj (List<Object> lista)
	{
	    for (Object element : lista)
	        System.out.println(element + " ");
	
	    System.out.println();
	}
	
	// ovakav metod može da štampa samo listu elemenata tipa Object
	// ne može da štampa npr. listu elemenata tipa String ili Integer
	// iako ti tipovi nasleđuju objekat
	// jer, kao što znamo,
	// Klasa<MajkaKlasa> i Klasa<ĆerkaKlasa> nisu u odnosu nasleđivanja
	// iako MajkaKlasa i ĆerkaKlasa jesu

	// ----------------------------------------------------------------
	
	// ako želimo pravu univerzalnost, argument treba da bude List<?>
	// zato što svaka klasa List<BiloŠta> nasleđuje klasu List<?>
	
	
	public static void štampajListuDžoker (List<?> lista)
	{
	    for (Object element: lista)
	        System.out.print(element + " ");
	    
	    System.out.println();
	}
	
	// ovo će već da radi za Lista<Ovo>, za Lista<Ono> itd

	public static void main(String args[])
	{
	
		List<Integer> li = Arrays.asList(1, 2, 3);
		List<String>  ls = Arrays.asList("one", "two", "three");
		štampajListuDžoker(li);
		štampajListuDžoker(ls);
		
		// a propo Oracle priče o dokerizaciji klasa
		// da probamo da insertujemo nešto u listu koja implementira List<?>
		// List<?> listJoker = new ArrayList<>();
		// listJoker.add(new Object());
		// ne dopušta
		// u listu koja implementira List<?> može da se ubaci samo null
	}	
}