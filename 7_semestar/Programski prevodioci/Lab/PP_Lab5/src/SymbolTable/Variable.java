package SymbolTable;

public class Variable extends SymbolNode {
	
	public int last_def;
	public int last_use;
	public int level;
	public boolean isInitialized = false;
	
	public Variable( String name, Type type, SymbolNode next, int level )
	{
		super( name, SymbolNode.VARIABLE, type, next );
		last_def = -1;
		last_def = -1;
		this.level = level;
	}
	
	public void setAsInitialized() {
		this.isInitialized = true;
	}
	
}
