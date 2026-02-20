public class ForStatement extends Statement {

    private Expression fromExpression;
    private Expression toExpression;
    private Statement block;
    private Variable var;

    public ForStatement(Expression fr, Expression to, Statement b, Variable v)
    {
        this.fromExpression = fr;
        this.toExpression = to;
        this.block = b;
        this.var = v;
    }

    void translate(BufferedWriter out) throws IOException
    {
        String startLab = ASTNode.genLab();
        String endLab = ASTNode.genLab();

        fromExpression.translate(out);
        toExpression.translate(out);
        fromExpression.genLoad("R1", out);
        out.write("\tStore R1, " + var.name);
        out.newLine();

        out.write(startLab + ":");
        out.newLine();

        toExpression.genLoad("R2", out);

        out.write("\tCompare_Less R2, R1");
        out.newLine();

        out.write("\tJumpIfNotZero R2, " + endLabel);
        out.newLine();

        block.translate();

        out.write("\tLoad_Mem R1, " + var.name);
        out.newLine();

        out.write("\tLoad_Const R2, 1");
        out.newLine();

        out.write("\tAdd R1, R2");
        out.newLine();

        out.write("\tStore R1, " + id.name);
        out.newLine();

        out.write("\tJump R2, " + startLabel);
        out.newLine();

        out.write(endLabel + ":");
        out.newLine();
    }
}