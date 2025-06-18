import java.util.*;

class Box<T> {
	
    private T t; // T kao Tip          
    
    public void set(T t) {
        this.t = t;
    }
 
    public T get() {
        return t;
    }
}



class BoxDemo {
	
	// generički metod addBox (klassa nije generička)
	// metod ima tipski parametar U
	// i drugi argument mu je fabrička lista elemenata Box<U>
	
	// fabrička lista je klasa List iz paketa java.util
	// importovali smo
	// ta klasa je generička, zapravo je List<>
	
	// element koji je prvi argument stavlja u objekat klase Box
	// i taj objekat onda trpa u listu zvanu boxes
	
	// objekat klase Box je parametrizovan tipom koji je prosleđem
	// metodu kao prvi argument
	
	public static <U> void addBox(U u, List<Box<U>> boxes)
	{
		Box<U> box = new Box<>();
		box.set(u);
		boxes.add(box);
	}

	public static <U> void outputBoxes(List<Box<U>> boxes)
	{
		int counter = 0;	// samo koliko da broji elemente jedan po jedan
		
		for (Box<U> box: boxes)	// foreach
		{
			U boxContents = box.get();
			System.out.println("Box #" + counter + " contains: " + boxContents.toString());
			counter++;
		}
	}

}

public class MainClass {
	
	  public static void main(String[] args)
	  {
		  ArrayList<Box<Integer>> listOfIntegerBoxes = new ArrayList<>();
		  
		  // klasičan poziv, tip je prosleđen kroz dijamant
		  // izraz je "type witness"
		  BoxDemo.<Integer>addBox(Integer.valueOf(10), listOfIntegerBoxes);
		  
		  // poziv bez prosleđivanja tipa
		  // kompajler će na osnovu argumenata da zaključi sam
		  BoxDemo.addBox(Integer.valueOf("20"), listOfIntegerBoxes);
		  BoxDemo.addBox(Integer.valueOf("30"), listOfIntegerBoxes);
		  
		  // štampanje
		  BoxDemo.outputBoxes(listOfIntegerBoxes);

	  }
	  
}
