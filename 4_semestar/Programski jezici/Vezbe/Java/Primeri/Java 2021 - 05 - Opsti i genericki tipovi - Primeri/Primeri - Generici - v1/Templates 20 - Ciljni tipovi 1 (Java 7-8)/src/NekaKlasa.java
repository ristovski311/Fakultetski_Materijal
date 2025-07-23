import java.util.*;

public class NekaKlasa <T> {
	
	public NekaKlasa() {}
	
	public static <T> NekaKlasa<T> nekiMetod() { return null; }
	
	// metod nekiMetod koji je parametrizovan tipom T
	
	// i koji vraća tip parametrizovane klase NekaKlasa<T>
	
	public static void drugiMetod(List<String> ls)
	{
		// drugi metod ima fiksno parametrizovani argument
		// (predefinisan parametarski tip)
		
		// ovde će se razlikovati kako se poziva iz Jave 7 i 8
		
		// kod Jave 7 neće umeti da izvede ciljni tip
		// kod Jave 8 će umeti
		
		// primeri poziva su dole u main klasi
	}
	
	
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
		
		// ----------------------------------------------------------
		
		// pozivamo drugi metod na način za Javu 7:
		
		NekaKlasa.drugiMetod(Collections.emptyList());
		// ovo neće da prođe kod Jave 7
		// javiće grešku:
		// List<Object> cannot be converted to List<String>
		
		// kod Jave 7 se mora napisati ovako:
		NekaKlasa.drugiMetod(Collections.<String>emptyList());
		
		// kod Jave 8 ono gore može da radi
		// jer kompajler ume da zaključi o tipu i u toj situaciji
		
		// znači kod Jave 7 nisu bile pokrivene situacije
		// kada treba sračunati tip kod artumenata metoda
		// a kod Jave 8 je i to pokriveno
	}

}
