public class AssignExpression extends Expression
{
    private Variable id;
    private Expression e;

    public abstract String operation();
    
    public AssignExpression(Variable id, Expression e, String op)
    {
        this.id = id;
        this.e = e;
        this.operation = op;
    }

    void translate(BufferedWriter out) throws IOException
    {
        e.translate(out);
        e.genLoad("R1", out);

        if(operation != "=")
        {
            out.write("\tLoad_Mem\tR2, " + id.name);
            out.newLine();

            if(operation == "+=")
                out.write("\tAdd R2, R1\n");
            else if(operation == "-=")
                out.write("\tSub R2, R1\n");
            else if(operation == "*=")
                out.write("\tMul R2, R1\n");
            else if(operation == "/=")
                out.write("\tDiv R2, R1\n");
        }

        out.write("\tStore\tR1, " + id.name);
        out.newLine();
    }
}