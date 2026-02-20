public class LoopStatement extends Statement
{
    private ArrayList<Statement> statements;

    public LoopStatement(ArrayList<Statement> s)
    {
        this.statements = s;
    }

    void translate(BufferedWriter out) throws IOException
    {
        String startLabel = ASTNode.genLab();
        String endLabel = ASTNode.genLab();

        out.write(startLabel + ":");
        out.newLine();

        for(Statement s : statements)
        {
            if(s instanceof ExitStatement)
            {
                ((ExitStatement)s).setEndLabel(endLabel);
            }
            s.translate(out);
        }

        out.write("\tJump\t" + startLabel);
        out.newLine();

        out.write(endLabel + ":");
        out.newLine();
    }
}