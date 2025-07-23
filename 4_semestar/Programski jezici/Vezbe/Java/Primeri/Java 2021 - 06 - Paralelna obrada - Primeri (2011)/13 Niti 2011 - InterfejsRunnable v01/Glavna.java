class Glavna
	{
	public static void main(String args[])
	{
		Nit n1 = new Nit("Thread 1",500);
		Nit n2 = new Nit("Thread 2",250);
		Nit n3 = new Nit("Thread 3",1000);
		n1.start();
		n2.start();
		n3.start();
	}
}
