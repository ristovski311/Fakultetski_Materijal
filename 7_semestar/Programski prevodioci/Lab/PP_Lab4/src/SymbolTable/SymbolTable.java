package SymbolTable;

public class SymbolTable {
	
	/*tabela simbola za "language scope"
	u ovom slucaju tu pripadaju samo tipovi*/
	private SymbolNode types;
	
	/* tabela simbola za oblast vazenja programa */
	private SymbolNode variables;
	
	private int currentScopeLevel = 0;
	
	public SymbolTable( )
	{
		types = new Type( "unknown", Type.UNKNOWN, null);
		types = new Type( "boolean", Type.BOOLEAN, types );
		types = new Type( "real", Type.REAL, types );
		types = new Type( "int", Type.INTEGER, types );
		variables = null;
	}
	
	public void enterScope() {
		currentScopeLevel++;
	}
	
	public void exitScope() {
		while (variables != null && ((Variable)variables).level == currentScopeLevel) {
            variables = variables.next;
        }
		currentScopeLevel--;
	}
	
	public int getCurrentLevel() {
		return currentScopeLevel;
	}
	
	public boolean addVar( String name, Type type)
	{
		SymbolNode current = variables;
        while (current != null && ((Variable)current).level == currentScopeLevel) {
            if (current.name.equals(name)) return false; 
            current = current.next;
        }
        variables = new Variable(name, type, variables, currentScopeLevel);
        return true;
	}
	
	public Variable getVar( String name )
	{
		SymbolNode current = variables;
        while (current != null) {
            if (current.name.equals(name)) return (Variable) current;
            current = current.next;
        }
        return null;
	}
	
	public Type getType(String typeName)
	{
		SymbolNode current = types;
		while ( current != null && 
				current.name.compareTo( typeName ) != 0 )
			current = current.next;
		return ( Type ) current;
	}
	
	public SymbolNode getVariables()
	{
		return variables;
	}

}
