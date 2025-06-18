
public class UređeniPar<K, V> implements Par<K, V> {

	private K ključ;
	private V vrednost;
	
	public UređeniPar(K ključ, V vrednost)
	{
		this.ključ = ključ;
		this.vrednost = vrednost;
	}
	
	public K getKljuč() { return ključ; }


	public V getVrednost() { return vrednost; }

}
