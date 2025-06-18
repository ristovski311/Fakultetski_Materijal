
class Razlomak {
	
	private int imenilac, brojilac;
	
	public Razlomak (int b, int i) throws RazlomakNedefinisan
	{
		if (i==0) throw new RazlomakNedefinisan();
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
