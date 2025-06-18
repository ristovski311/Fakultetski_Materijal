
public class MainClass {
	
	public static void main(String args[])
	{
		UređeniPar<Integer, String> up1 = new UređeniPar<Integer, String>(1,"2");
		
		// Konstruktor je, kao metod, neparametrizovan.
		// Pa ipak, ako desno izbacimo dijamant, dobićemo warning.
		// Parametrizovani metodi se rade u nastavku.
		
		System.out.println(up1.getKljuč());
		System.out.println(up1.getVrednost());
		
		UređeniPar<Float, Double> up2 = new UređeniPar<>(1.1f, 2.2);

	}

}
