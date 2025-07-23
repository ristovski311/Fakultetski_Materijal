
// klasa nije generička, a konstruktor jeste

public class NekaKlasa {
	
	public <T> NekaKlasa(T t)
	{
		System.out.println(t.getClass());
	}
	
}

// neparametarska (ne-generička) klasa
// a parametrizovan (generički) konstruktor

// prilikom instanciranja ne moramo uopšte da stavimo dijamant
// levo ionako ne možemo, jer klasa nije parametrizovana
// desno možemo, ali ako ne stavimo, kompajler će zaključiti

// i ako skroz izostavimo dijamant to se neće smatrati raw objektom
