package AST;

public class LessEqualExpression extends RelExpression {

	public LessEqualExpression(Expression l, Expression r) {
		super(l, r, true); //Prvo da li je vece proveravamo (>), pa inverziju tog rezultata
	}

	protected String opCode() {
		return "Compare_Greater"; 
	}
	
}
