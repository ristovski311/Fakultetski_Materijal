
// klasa je parametrizovana jednim parametrom
// konstruktor je parametrizvan ali DRUGIM parametrom

public class NekaKlasa<X> 
{
	
	public <T> NekaKlasa(T t)
	{
		System.out.println(t.getClass());
	}

	public static void main(String args[])
	{
		NekaKlasa <String> nk1 = new NekaKlasa<>(new Integer(10));
	}
}

// kompajler će da provali da treba da instancira sa X = String
// jer je to navedeno na levoj strani izrara

// kompajler će da provali da je parametar konstruktora T = Integer