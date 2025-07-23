package matematika;

public class KvadratnaFunkcija implements Funkcija {
	
	private double a,b,c;
	
	public KvadratnaFunkcija(double aa, double bb, double cc)
	{
		a = aa;
		b = bb;
		c = cc;
	}
	
	public double vrednost(double x)
	{
		return a*x*x + b*x + c;
	}
	
	public boolean imaRealneNule()
	{
		if (a==0 || (b*b-4*a*c)<0) return false;
		else return true;
	}
	
	public double[] nule()
	{
		double[] pom = new double[2];
		pom[0] = (((-1)*b) + Math.sqrt(b*b-4*a*c)) / (2*a);
		pom[1] = (((-1)*b) - Math.sqrt(b*b-4*a*c)) / (2*a);
		return pom;
	}

}
