public class WhileLoop extends Statement
{
    private ArrayList<Statement> statements;
    private ArrayList<Expression> conditions;

    public WhileLoop(ArrayList<Statement> st, ArrayList<Expression> con)
    {
        this.statements = st;
        this.conditions = con;
    }

    void translate(BufferedWriter out) throws IOException
    {
        String startLab = ASTNode.genLab();
        String endLab = ASTNode.genLab();

        out.write(startLab + ":");
        out.newLine();

        for(Expression e : conditions)
        {
            e.translate(out);
            e.genLoad(out);
            out.write("\tJumpIfZero\tR1, " + endLab);
            out.newLine();
        }

        for(Statement s : statemens)
        {
            s.translate(out);
        }

        out.write("\tJump\t"+startLab);
        out.newLine();

        out.write(endLab + ":");
        out.newLine();
    }
}