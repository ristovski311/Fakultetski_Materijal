public class ForStatement extends Statement
{
    private Expression fromEx;
    private Expression toEx;
    private Statement statement;
    private Variable id;
    private Constant constant;

    public ForStatement(Expression e1, Expression e2, Statement s, Variable v, Constant c)
    {
        this.fromEx = e1;
        this.toEx = e2;
        this.statement = s;
        this.id = v;
        this.const = c;
    }

    void translate(BufferedWriter out) throws IOException
    {
        String startLab = ASTNode.genLab();
        String endLab = ASTNode.genLab();

        fromEx.translate(out);
        toEx.translate(out);

        fromEx.genLoad("R1", out);
        out.write("\tStore\tR1, " + id.name);
        out.newLine();
        
        out.write(startLab + ":");
        out.newLine();

        toEx.genLoad("R2", out);

        out.write("\tCompare_Less\tR2, R1");
        out.newLine();

        out.write("\tJumpIfNotZero\tR2, " + endLabel);
        out.newLine();

        statement.translate(out);

        out.write("\tLoad_Mem\tR1, " + id.name);
        out.newLine();

        out.write("\tLoad_Const\tR2, " + constant.value);
        out.newLine();

        out.write("\tAdd\tR1, R2");
        out.newLine();

        out.write("\tStore\tR1, " + id.name);
        out.newLine();

        out.write("\tJump\t" + startLab);
        out.newLine();

        out.write(endLab + ":");
        out.newLine();
    }

}