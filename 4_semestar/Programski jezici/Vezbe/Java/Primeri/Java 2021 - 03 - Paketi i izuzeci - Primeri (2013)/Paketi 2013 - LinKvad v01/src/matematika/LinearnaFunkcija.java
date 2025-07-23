package matematika;

public class LinearnaFunkcija implements Funkcija {
	
	private double a,b;
	
	public LinearnaFunkcija(double aa, double bb)
	{
		a = aa;
		b = bb;
	}
	
	public double vrednost(double x)
	{
		return a*x+b;
	}
	
	public boolean imaRealneNule()
	{
		if (b != 0) return true;
		else return false;
	}
	
	public double[] nule()
	{
		double[] pom = new double[1];
		pom[0] = -b/a;
		return pom; 
	}

}
