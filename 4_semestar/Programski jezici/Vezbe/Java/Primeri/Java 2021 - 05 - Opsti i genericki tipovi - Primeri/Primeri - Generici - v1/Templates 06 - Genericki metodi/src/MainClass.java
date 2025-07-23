
public class MainClass {
	
	public static void main (String args[])
	{
		Par<Integer, String> p1 = new Par<>(1,"a");
		// da nismo stavili prazan dijamant desno
		// imali bismo warning da je desno sirov tip
		// iako bi kompajler zaključio o tipu
		// međutim sa praznim dijamantom smo sigurni
		
		Par<Integer, String> p2 = new Par<>(2,"b");
		
		System.out.println(Alat.<Integer, String>uporedi(p1, p2));
		// kad zovemo parametrizovani metod tipove stavljamo pre imena metoda
		
		System.out.println(Alat.uporedi(p1, p2));
		// u ovom slučaju ne moramo da definišemo parametarske tipove
		// jer će kompajler sam da ih provali
		// a to što smo izostavili i prazan dijamant
		// u ovom slučaju ne pravi problem (sirovi tip)
		// jer je u pitanju metod, a ne tip
		// a metod ne može biti sirov <------------------------ PROVERI OVO
		
		System.out.println(Alat.uporedi(10, 10));
		// neparametrizovani metod sa istim imenom
	}

}
