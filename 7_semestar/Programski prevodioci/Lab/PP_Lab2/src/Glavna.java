import java.io.IOException;

public class Glavna {

	public static void main(String[] args) throws IOException {
		LRSyn s = new LRSyn("src/testinput3.txt");
		boolean result = s.SA_LR();
		if(result)
			System.out.println("Sintaksno je korektno!");
		else
			System.out.println("Postoji sintaksna greska!");
	}
}
