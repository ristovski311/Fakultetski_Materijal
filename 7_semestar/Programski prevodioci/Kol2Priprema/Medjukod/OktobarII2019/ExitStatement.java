public class ExitStatement extends Statement
{
    private Expression condition;
    private String endLabel;

    public ExitStatement(Expression cond, String el)
    {
        this.condition = cond;
        this.endLabel = el;
    }

    void setEndLabel(String l)
    {
        this.endLabel = l;
    }

    void translate(BufferedWriter out) throws IOException
    {
        condition.translate(out);
        condition.genLoad("R1", out);
        out.write("\tJumpIfNotZero\tR1, " + endLabel);
        out.newLine();
    }


}