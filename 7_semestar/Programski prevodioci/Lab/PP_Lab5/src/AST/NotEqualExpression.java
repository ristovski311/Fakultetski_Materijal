package AST;

public class NotEqualExpression extends RelExpression {

	public NotEqualExpression(Expression l, Expression r) {
		super(l, r, true); //Potrebna je negacija jer koristimo poredjenje prvo (==), pa invertujemo taj rezultat
	}

	protected String opCode() {
		return "Compare_Equal"; 
	}
	
}
