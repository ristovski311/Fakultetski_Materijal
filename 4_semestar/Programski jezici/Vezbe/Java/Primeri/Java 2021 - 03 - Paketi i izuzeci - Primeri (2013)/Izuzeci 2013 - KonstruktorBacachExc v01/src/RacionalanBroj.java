
class RacionalanBroj {
	
	@SuppressWarnings("unused")
	private int imenilac, brojilac;
	
	public RacionalanBroj (int b, int i) throws Exception
	{
		if (i==0) throw new Exception("Razlomak nedefinisan!");
		else
		{
			imenilac = i;
			brojilac = b;
			System.out.println("Formiran razlomak: "+b+"/"+i);
			// Ovaj red u konstruktoru sluzi da nas obavesti da je kreiranje
			// objekta proslo bez problema. Inace, nije uobicajeno da
			// konstruktori stampaju bilo sta.
		}
	}

}
