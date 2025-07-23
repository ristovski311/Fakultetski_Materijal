
class Glavna {
	
	public static void main(String args[])
	{
		@SuppressWarnings("unused")
		RacionalanBroj razlomak1, razlomak2;
		
//		razlomak1 = new Razlomak(1,2);	// ovo nece dopustiti van try bloka
										// javice da nije pokriven moguci
										// izuzetak (unhandled exception)
										// (ukloniti // ispred naredbe i proveriti)
		
		try
		{
			razlomak1 = new RacionalanBroj(1,2);	// ovo treba da prodje
			razlomak2 = new RacionalanBroj(4,0);	// ovo bi trebalo da baci izuzetak
		}
		catch (Exception e)
		{
			System.out.println(e);
		}
	}

}
