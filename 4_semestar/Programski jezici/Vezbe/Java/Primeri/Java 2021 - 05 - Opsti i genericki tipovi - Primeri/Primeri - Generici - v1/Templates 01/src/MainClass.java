// Baledung sajt (zeleni) za templejte (Java Generics)
// https://www.baeldung.com/java-generics

// Primer 1: zašto nam trebaju generički tipovi

import java.util.*;

public class MainClass {
	
	public static void main(String args[])
	{
		List list = new LinkedList();
		list.add(1);
		
		Integer i = (Integer)list.iterator().next(); // kompajler traži cast na Integer
		
		int ii = (int) list.iterator().next(); // kompajler traži cast na int
	}

}
