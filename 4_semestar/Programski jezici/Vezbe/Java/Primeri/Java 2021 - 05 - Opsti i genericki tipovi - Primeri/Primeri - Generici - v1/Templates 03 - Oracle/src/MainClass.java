
public class MainClass {
	
	public static void main(String args[])
	{
		GenericBox<String> gbs = new GenericBox<String>();
		GenericBox<Integer> gbi = new GenericBox<>();	// Jasno je da je <Integer>
		
		System.out.println(gbs +" "+ gbi);
	}

}
