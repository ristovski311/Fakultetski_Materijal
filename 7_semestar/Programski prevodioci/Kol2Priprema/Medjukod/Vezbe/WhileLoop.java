public class WhileStatement extends Statement
{
    public Expression condition;
    public Statement statement;

    public WhileStatement(Expression cond, Statement st)
    {
        this.condition = cond;
        this.statement = st;
    }

    public void translate(BufferedWriter out) throws IOException
    {
        String startLabel = ASTNode.genLab();
        String endLabel = ASTNode.genLab();

        //label0 - while loop
        out.write(startLabel + ":");
        out.newLine();

        //Izvrsenje uslova
        this.condition.translate(out);
        this.condition.getLoad("R1", out);

        //U R1 je rezultat uslova, ako je 0 (nije ispunjen) izlazimo iz while loop
        out.write("\tJumpIfZero\tR1, " + endLabel);
        out.newLine();

        //Ako nismo skocili radimo telo petlje, pa skacemo na pocetak opet
        this.statement.translate();
        out.write("\tJump " + startLabel);
        out.newLine();

        //Ovde stampamo endlabel
        out.write(endLabel + ":");
        out.newLine();
    }
}