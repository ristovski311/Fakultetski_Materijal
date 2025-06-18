
class RacionalanBroj {
	
	private int imenilac, brojilac;
	
	public RacionalanBroj (int b, int i)
	{
		imenilac = i;
		brojilac = b;
		
	}
	
	public double Vrednost() throws RazlomakNedefinisan
	{
		if (imenilac==0) throw new RazlomakNedefinisan();
		else return ((double)brojilac)/((double)imenilac);
	}

}
