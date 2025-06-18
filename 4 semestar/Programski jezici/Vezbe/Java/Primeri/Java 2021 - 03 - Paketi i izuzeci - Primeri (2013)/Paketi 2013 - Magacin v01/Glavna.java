public class Glavna {
	
	public static void main(String[] args) {
		
		kolekcija.Magacin stek = new kolekcija.Magacin();

		
		for (int i=0; i<10; i++)
		{
			int k = (int)(10*Math.random());
			stek.push(new Integer(k));			// pravi se novi objekat tipa Integer,
												// daje mu se vrednost i prosledjuje se
												// metodu - jer metod ocekuje neki
												// referentni tip.
		}

//		Posto se nizovi smatraju referentnim tipovima, metodu push mozemo da "podmetnemo"
//		i niz kao argument - kompajler nece prijaviti gresku. Medjutim, dobicemo
//		prilicno besmislen rezultat.
//		int[] iii = new int[5];
//		stek.push(iii);
		
		
		while (!stek.prazanJe())
			System.out.println(stek.pop().toString());
	}

}
