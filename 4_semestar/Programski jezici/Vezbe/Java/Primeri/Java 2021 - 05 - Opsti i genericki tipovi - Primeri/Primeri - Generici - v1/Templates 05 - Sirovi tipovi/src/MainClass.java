
public class MainClass {
	
	public static void main(String args[])
	{
		UređeniPar up1 = new UređeniPar(1,2); // sam je izveo tipove svuda
		
		System.out.println(up1.getKljuč());
		System.out.println(up1.getVrednost());
		
		UređeniPar<Integer, String> up2 = new UređeniPar(1,"a"); // sam je izveo tipove desno
		
		UređeniPar<Float, Double> up3 = new UređeniPar<>(1.1f, 2.2);	// dijamanat
																		// nema warninga
		
		// warninzi gore na raw tipove nude kao jedan od quickfixeva
		// da se refaktoriše kod tako što će da izvede (inferuje) tipove
		// i da ih tako izvedene eksplicitno doda u kod
	}

}
