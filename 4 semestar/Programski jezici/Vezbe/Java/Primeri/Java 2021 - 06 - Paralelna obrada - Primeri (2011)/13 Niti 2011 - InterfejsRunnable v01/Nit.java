class Nit implements Runnable
{
	private Thread t;
	private int sleepTime;
	public Nit(String name, int time)
	{
		sleepTime = time;
		t = new Thread(this, name);
	}
	public void start()
	{
		t.start();
	}
	public void run()
	{
		for (int i=1; i<10; i++)
		{
			try
			{
				Thread.sleep(sleepTime);
			}
			catch (InterruptedException e){}
			System.out.println("U iteraciji "+i+" proces "+t.getName()+" je spavao " + sleepTime+"ms");
		}
	}
}
