
public class NekaKlasa <T> {
	
	public NekaKlasa() {}
	
	public static <T> NekaKlasa<T> nekiMetod() { return null; }
	
	// metod nekiMetod koji je parametrizovan tipom T
	
	// i koji vraća tip parametrizovane klase NekaKlasa<T>
	
	
	public static void main(String args[])
	{
		
		// poziv metoda nekiMetod bez da njemu prosledimo tip
		
		NekaKlasa<String> nk1 = NekaKlasa.nekiMetod();
		
		// ovde je očekivano da metod vrati objekat tipa NekaKlasa<String>
		// za taj tip se kaže da je ciljni tip (target type)
		
		// metod u opštem slučaju vraća objekat tima NekaKlasa<T>
		// i na osnovu toga kompajler zaključuje da to T
		// treba da bude String
		
		// možemo pedantno i da naglasimo tip kod poziva metoda
		// odnosno da iskoristimo "type witness"
		
		NekaKlasa<String> nk2 = NekaKlasa.<String>nekiMetod();
		
		// u ovom kontekstu to nije neophodno
		
		// a ako bismo kod poziva metoda prosledili neki drugi tip
		// dobili bismo grešku
		
		// NekaKlasa<String> nk2 = NekaKlasa.<Integer>nekiMetod();
	}

}
