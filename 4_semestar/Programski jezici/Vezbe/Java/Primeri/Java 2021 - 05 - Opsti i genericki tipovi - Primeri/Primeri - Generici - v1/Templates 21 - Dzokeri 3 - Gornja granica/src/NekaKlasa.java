// Džoker ograničen odozdo.

// Ključna reč: super

// 

import java.util.*;	// za interfejs List i sl.

public class NekaKlasa {
	
	public static void dodaj10IntegeraUListu (List<? super Integer> lista)
	{
	    for (int i = 1; i <= 10; i++) {
	        lista.add(i);	// metod klase 
	    }
	}
	
	public static void main (String args[])
	{
		List<Number> ln = new ArrayList<>();
		
		dodaj10IntegeraUListu(ln);
	}
	

}
