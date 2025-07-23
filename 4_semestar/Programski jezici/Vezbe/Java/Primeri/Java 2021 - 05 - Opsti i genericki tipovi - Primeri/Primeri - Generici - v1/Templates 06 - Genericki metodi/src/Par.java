
public class Par <K, V>
{
	private K ključ;
	private V vrednost;
	
	public Par (K ključ, V vrednost)
	{
		this.ključ = ključ;
		this.vrednost = vrednost;
	}
	
	public void setKljuč (K ključ) { this.ključ = ključ; }
	
	public void setVrednost (V vrednost) { this.vrednost = vrednost; }
	
	public K getKljuč () { return ključ; }
	
	public V getVrednost () { return vrednost; }
	
}
