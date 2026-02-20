

import java.util.Hashtable;
public class KWTable {

	private Hashtable mTable;
	public KWTable()
	{
		// Inicijalizcaija hash tabele koja pamti kljucne reci
		mTable = new Hashtable();
		mTable.put("main", sym.MAIN);
		mTable.put("int", sym.INT);
		mTable.put("real", sym.REAL);
		mTable.put("boolean", sym.BOOLEAN);
		//mTable.put("true", sym.TRUE);
		//mTable.put("false", sym.FALSE);
		mTable.put("if", sym.IF);
		mTable.put("elif", sym.ELIF);
		mTable.put("else", sym.ELSE);		
	}
	
	/**
	 * Vraca ID kljucne reci 
	 */
	public int find(String keyword)
	{
		Object symbol = mTable.get(keyword);
		if (symbol != null)
			return ((Integer)symbol).intValue();
		
		// Ako rec nije pronadjena u tabeli kljucnih reci radi se o identifikatoru
		return sym.ID;
	}
	

}
