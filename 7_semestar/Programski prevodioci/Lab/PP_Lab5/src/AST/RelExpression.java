package AST;

import java.io.*;

public abstract class RelExpression extends Expression {

	private Expression right;
	private Expression left;
	private boolean isNegation;
	
	public RelExpression(Expression l, Expression r, boolean isNeg)
	{
		this.left = l;
		this.right = r;
		this.isNegation = isNeg;
	}
	
	protected abstract String opCode();
	
	public void translate(BufferedWriter out) throws IOException
	{
		left.translate(out);
		right.translate(out);
		left.genLoad("R1", out);
		right.genLoad("R2", out);
		
		out.write("\t" + opCode() + "\t\tR1, R2");
		out.newLine();
		// Za <=, >= i <>
		if(isNegation)
		{
			out.write("\tCompare_Equal\t\tR1, 0");
			out.newLine();
		}
		
		this.result = ASTNode.genVar();
		out.write("\tStore\t\tR1, " + this.result);
		out.newLine();
	}
	
}
