import java.util.*;	// za interfejs List

public class HvatanjeDzokeraNeuspelo
{
	void nekiMetod(List<?> i) {
		
        i.set(0, i.get(0));	// neće moći
        
    }
	
	// kompajler prvo argument i proglasi za tip object
	// onda se pokrene metod set
	// kompajler ne može da proceni tip objekta koji se ubacuje u listu
	
	// to znači da kompajler misli da je promenljivoj dat pogrešan tip

}
