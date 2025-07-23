// ovakva situacija se ne može ispraviti ni helper metodima

import java.util.*;

public class NepopravljivoLošeHvatanjeDžokera {
	
	public static void zameniPrviElement(List<? extends Number> lista1, List<? extends Number> lista2)
	{
		
	      Number temp = lista1.get(0);
	      
	      lista1.set(0, lista2.get(0));	// očekivano: CAP#1 extends Number,
	                            		// dobijeno:  CAP#2 extends Number;
	      
	      								// ista granica, ali različiti tipovi
	      
	      lista2.set(0, temp);	    	// očekivano: CAP#1 extends Number,
	                            		// dobijeno:  Number
	}
	
	public static void main (String args[])
	{
		
		List<Integer> li = Arrays.asList(1, 2, 3);
		List<Double>  ld = Arrays.asList(10.10, 20.20, 30.30);
		zameniPrviElement(li, ld);
		
	}

}
