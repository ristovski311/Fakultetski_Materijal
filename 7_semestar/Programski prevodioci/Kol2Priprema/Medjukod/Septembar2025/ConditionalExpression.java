public class ConditionalExpression extends Expression
{
    private Expression condition;
    private Expression valueLess;
    private Expression valueZero;
    private Expression valueGreater;

    public ConditionalExpression(Expression e1,Expression e2,Expression e3,Expression e4)
    {
        this.condition = e1;
        this.valueLess = e2;
        this.valueZero = e3;
        this.valueGreater = e4;
    }

    void translate(BufferedWriter out) throws IOException
    {
        String manjeJednakoLabel = ASTNode.genLab();
        String jednakoLabel = ASTNode.genLab();
        String krajLabel = ASTNode.genLab();

        condition.translate(out);
        condition.genLoad("R1", out);

        out.write("\tLoad_Const\tR2, 0");
        out.newLine();

        out.write("\tCompare_Less\tR2, R1");
        out.newLine();

        out.write("\tJumpIfZero\t" + manjeJednakoLab);
        out.newLine();

        valueGreater.translate(out);
        valueGreater.genLoad("R1", out);
        
        out.write("\tJump\t" + krajLabel);
        out.newLine();

        out.write(manjeJednakoLab + ":");
        out.newLine();

        out.write("\tLoad_Const\tR2, 0");
        out.newLine();

        out.write("\tCompare_Greater\tR2, R1");
        out.newLine();

        out.write("\tJumpIfZero\tR2, " + jednako);
        out.newLine();

        valueLess.translate(out);
        valueLess.genLoad("R1", out);

        out.write("\tJump\t" + krajLabel);
        out.newLine();

        out.write(jednakoLabel + ":");
        out.newLine();

        valueZero.translate(out);
        valueZero.genLoad("R1", out);

        out.write(krajLabel + ":");
        out.newLine();

        super.result = ASTNode.genVar();
        out.write("\tStore\tR1, " + super.result);
        out.newLine();
    }
}