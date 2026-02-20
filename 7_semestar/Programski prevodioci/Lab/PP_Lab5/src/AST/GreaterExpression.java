package AST;

public class GreaterExpression extends RelExpression{

	public GreaterExpression(Expression l, Expression r) {
		super(l, r, false);
	}

	protected String opCode() {
		return "Compare_Greater"; 
	}
	
}
