package AST;

public class EqualExpression extends RelExpression{

	public EqualExpression(Expression l, Expression r) {
		super(l, r, false); //False zato sto nam nije potrebno da inverujemo rezultat, jer nam je rezultat vec u tom registru, da je <>, posto se on sluzi Compare_Equal, morala bi negacija
	}

	protected String opCode() {
		return "Compare_Equal"; 
	}
}
