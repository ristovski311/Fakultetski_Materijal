public class CondStatement extends Statement
{
    private Statement statement;
    private Expression condition;
    private boolean isUnless;

    public CondStatement(Statement s, Expression c, boolean unless)
    {
        this.statement = s;
        this.condition = c;
        this.isUnless = unless;
    }

    void translate(BufferedWriter out) throws IOException
    {
        String endLabel = ASTNode.genLab();

        condition.translate(out);
        condition.genLoad("R1", out);

        if(isUnless)
        {
            out.write("\nJumpIfNotZero\tR1, " + endLabel);
            out.newLine();
        }
        else
        {
            out.write("\nJumpIfZero\tR1, " + endLabel);
            out.newLine();
        }
        s.translate(out);

        out.write(endLabel + ":");
        out.newLine();
    }
}