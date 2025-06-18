/**
 * Generic version of the Box class.
 * @param <T> the type of the value being boxed
 */

public class GenericBox<T> {
	
	// T znači tip
	
	private T podatak;	// podatak-član unapred nepoznatog tipa
	
	public void set (T pod) { podatak = pod; }
	
	public T get () { return podatak; }

}
