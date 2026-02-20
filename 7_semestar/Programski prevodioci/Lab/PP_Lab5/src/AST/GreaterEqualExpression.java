package AST;

public class GreaterEqualExpression extends RelExpression {

	public GreaterEqualExpression(Expression l, Expression r) {
		super(l, r, true);
	}

	protected String opCode() {
		return "Compare_Less"; 
	}

}
