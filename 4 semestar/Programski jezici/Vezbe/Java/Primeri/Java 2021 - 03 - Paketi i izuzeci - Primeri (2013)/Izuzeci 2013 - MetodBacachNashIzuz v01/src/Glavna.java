
class Glavna {
	
	public static void main(String args[])
	{
		RacionalanBroj razlomak1, razlomak2;

		razlomak1 = new RacionalanBroj(1,2);	// nije rizicna operacija
		razlomak2 = new RacionalanBroj(4,0);	// nije rizicna operacija
		
		try
		{
			System.out.println("Vrednost prvog je: "+razlomak1.Vrednost());
			System.out.println("Vrednost drugog je: "+razlomak2.Vrednost()); // izuzetak
		}
		catch (RazlomakNedefinisan ndrz)
		{
			System.out.println(ndrz);
		}
	}

}
