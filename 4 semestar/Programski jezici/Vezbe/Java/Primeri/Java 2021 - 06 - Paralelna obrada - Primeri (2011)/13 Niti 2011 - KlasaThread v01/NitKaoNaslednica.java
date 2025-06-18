
public class NitKaoNaslednica extends Thread {
	
	public NitKaoNaslednica(String str)		// argument je ime niti
	{
		super(str);							// prosledjuje se natklasi
	}
	
	public void run()
	{
		for(int i=0; i<10; i++)
		{
			System.out.println(i+" "+getName());		// odstampaj svoje ime...
			try
			{
				sleep((long)(Math.random()*1000));		// ...a onda spavaj neko vreme!
			}
			catch(Exception e)
			{
				System.out.println("Izuzetak: "+getName());
			}
		}
		// kad zavrsis petlju, prijavi da si prosao kroz cilj
		System.out.println(getName()+" prodje kroz cilj!");
	}
}
