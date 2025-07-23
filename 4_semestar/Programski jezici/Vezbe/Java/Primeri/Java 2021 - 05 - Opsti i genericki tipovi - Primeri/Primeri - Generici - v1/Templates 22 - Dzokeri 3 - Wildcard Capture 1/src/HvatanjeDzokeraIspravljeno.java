import java.util.*;

public class HvatanjeDzokeraIspravljeno {
	
	void nekiMetod (List<?> i)
	{
        metodovHelper(i);
    }


    // problem sa hvatanjem džokera ovde rešavamo
    // privatnim helper metodom
	// koji hvatanje džokera rešava putem
	// mehanizma izvođenja tipova
	
	// putem izvođenja tipova kompajler zaključuje
	// da je CAP#1 (prvo hvatanje džokera) zapravo T
	
    private <T> void metodovHelper (List<T> l)
    {
        l.set(0, l.get(0));
    }


}
