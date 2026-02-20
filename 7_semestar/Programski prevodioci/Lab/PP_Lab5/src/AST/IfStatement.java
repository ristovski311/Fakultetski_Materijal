package AST;

import java.io.*;
import java.util.ArrayList;


public class IfStatement extends Statement{
	private Block ifBlock;
	private Block elseBlock;
	private Expression ifCondition;
	private ArrayList<Expression> elifExps = new ArrayList<Expression>();
	private ArrayList<Block> elifBlocks = new ArrayList<Block>();
	
	//Za potrebe slanja nagore u stintaksnom stablu
	
	public IfStatement()
	{
		
	}
	
	public IfStatement(Expression cond, Block ifBlock, ArrayList<Expression> elifExps, ArrayList<Block> elifBlocks, Block elseBlock) {
        this.ifCondition = cond;
        this.ifBlock = ifBlock;
        this.elifExps = elifExps;
        this.elifBlocks = elifBlocks;
        this.elseBlock = elseBlock;
    }
	
	//Za Elif neterminal
	public IfStatement(Expression cond, Block ifBlock) {
        this.ifCondition = cond;
        this.ifBlock = ifBlock;
    }
	
	
	public IfStatement(Expression cond, Block ifBlock, Block elseBlock) {
        this.ifCondition = cond;
        this.ifBlock = ifBlock;
        this.elseBlock = elseBlock;
    }
	
	//Dodavanje elif dela
	
	public void addElifPart(Expression e, Block b)
	{
		elifExps.add(e);
		elifBlocks.add(b);
	}
	
	//Getteri i setteri za if
	
		public void setIfBlock(Block b)
		{
			this.ifBlock = b;
		}
		
		public Block getIfBlock()
		{
			return ifBlock;
		}
		
		public Expression getIfCond()
		{
			return ifCondition;
		}
		
		public void setIfCond(Expression e)
		{
			this.ifCondition = e;
		}
	
		
	//Getteri i setteri za else
		
		public void setElseBlock(Block b)
		{
			this.elseBlock = b;
		}
		
		public Block getElseBlock()
		{
			return elseBlock;
		}
	
	public void translate( BufferedWriter out )
	throws IOException
	{
		String endLabel = ASTNode.genLab();
		String elseLabel = ASTNode.genLab();
		String nextLabel = ASTNode.genLab();
		
		//Glavni if
		ifCondition.translate(out);
		ifCondition.genLoad("R1", out);
		out.write("\tJumpIfZero\t\tR1, " + nextLabel);
		out.newLine();
		ifBlock.translate(out);
		out.write("\tJump\t\t" + endLabel);
		out.newLine();
		
		//Elif blokovi
		if(elifBlocks != null && elifExps != null)
		{
			for(int i = 0; i < elifExps.size(); i++)
			{
				out.write(nextLabel + ":");
				out.newLine();
				if(i == (elifExps.size() - 1))
					nextLabel = elseLabel;
				else
					nextLabel = ASTNode.genLab();
				elifExps.get(i).translate(out);
				elifExps.get(i).genLoad("R1", out);
				out.write("\tJumpIfZero\t\tR1, " + nextLabel);
				out.newLine();
				elifBlocks.get(i).translate(out);
				out.write("\tJump\t\t" + endLabel);
				out.newLine();
			}
		}
		
		//Else
		out.write(elseLabel + ":");
		out.newLine();
		if(elseBlock != null)
			elseBlock.translate(out);

		//Kraj
		out.write(endLabel + ":");
		out.newLine();
	}
}


