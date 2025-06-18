
class RacionalanBroj {
	
	private int imenilac, brojilac;
	
	public RacionalanBroj (int b, int i)
	{
		imenilac = i;
		brojilac = b;
		
	}
	
	public double Vrednost() throws Exception
	{
		if (imenilac==0) throw new Exception("Razlomak nedefinisan!");
		else return ((double)brojilac)/((double)imenilac);
	}

}
