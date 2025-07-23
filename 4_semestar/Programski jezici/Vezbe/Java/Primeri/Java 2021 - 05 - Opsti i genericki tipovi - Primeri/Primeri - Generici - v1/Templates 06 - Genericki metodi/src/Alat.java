
public class Alat {
	
	public static <K, V> boolean uporedi (Par <K, V> p1, Par <K, V> p2)
	{
		return p1.getKljuč().equals(p2.getKljuč()) && p1.getVrednost().equals(p2.getVrednost()); 
	}
	
	public static boolean uporedi (Integer a, Integer b)
	{
		return a.compareTo(b)==0;
	}

}
