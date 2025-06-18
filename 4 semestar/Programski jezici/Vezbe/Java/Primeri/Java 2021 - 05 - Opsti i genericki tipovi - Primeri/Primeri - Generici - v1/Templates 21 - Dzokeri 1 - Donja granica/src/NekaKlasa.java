// Džoker ograničen odozgo.
// Znači dolaze u obzir ograničavajući tip i njegovi podtipovi.
// U ovom slučaju Number i sve što ga nasleđuje.
// Legalno je korišćenje samo metoda iz klase Number.
// Jer svi nasleđeni tipovi sigurno imaju te metode.
// U ovom slučaju to je doubleValue() koju sadrži klasa Number.

import java.util.*;	// zbog interfejsa List

public class NekaKlasa {
	
	public static double sumaListe(List<? extends Number> arg)
	{
		double suma = 0.0;
		for (Number broj : arg)
		{
			suma += broj.doubleValue();	// ima ga klasa Number
		}
		return suma;
	}
	
	public static void main(String args[])
	{
		
		List<Integer> listaInt = Arrays.asList(1,2,3); // automatski kreira listu
		
		List<Double> listaDouble = Arrays.asList(1.1, 2.2, 3.3);
		
		System.out.println("Suma Integer liste: "+sumaListe(listaInt));
		
		System.out.println("Suma Double liste: "+sumaListe(listaDouble));
		
		// da probamo da insertujemo nešto u listu koja implementira List<?>
		// List<?> listJoker = new ArrayList<>();
		// listJoker.add(new Object());
		// ne dopušta
		// u listu koja implementira List<?> može da se ubaci samo null
		
	}

}
