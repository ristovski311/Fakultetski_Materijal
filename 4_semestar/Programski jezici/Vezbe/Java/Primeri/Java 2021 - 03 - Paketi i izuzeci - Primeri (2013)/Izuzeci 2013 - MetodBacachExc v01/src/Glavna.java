
class Glavna {
	
	public static void main(String args[])
	{
		RacionalanBroj razlomak1, razlomak2;
	
		// Kreranje objekata (sto podrazumeva pozivanje konstruktora
		// sad vise nisu rizicne operacije, jer konstruktor u ovom
		// primeru ne baca izuzetak (znaci ne vrsi nikakvu proveru)
		razlomak1 = new RacionalanBroj(1,2);	// ovo prolazi glatko
		razlomak2 = new RacionalanBroj(4,0);	// i ovo prolazi glatko

		try
		{
			System.out.println("Vrednost prvog je: "+razlomak1.Vrednost());
			System.out.println("Vrednost drugog je: "+razlomak2.Vrednost()); // izuzetak
		}
		catch (Exception e)
		{
			System.out.println(e);
		}
	}

}
