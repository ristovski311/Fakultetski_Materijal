package AST;

public class LessExpression extends RelExpression {

	public LessExpression(Expression l, Expression r) {
		super(l, r, false);
	}

	protected String opCode() {
		return "Compare_Less"; 
	}
	
}
