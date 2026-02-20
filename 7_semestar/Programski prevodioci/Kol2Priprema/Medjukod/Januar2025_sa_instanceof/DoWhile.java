public class DoWhileStatement extends Statement 
{
    public ArrayList<Statement> block;
    public Expression condition;
    
    //OVO RESENJE RADI (i hope)

    public DoWhileStatement(ArrayList<Statement> b, Expression c)
    {
        this.block = b;
        this.condition = c;
    }

    void translate(BufferedWriter out) throws IOException
    {
        String startLabel = ASTNode.genLab();
        String endLabel = ASTNode.genLab();
    
        out.write(startLabel + ":");
        out.newLine;

        for(Statement s : block)
        {
            if(s instanceof Break)
            {
                ((Break)s).setBreakLab(endLabel);
            }
            else if(s instanceof Continue)
            {
                ((Continue)s).setContinueLab(startLabel);
            }

            s.translate(out);
        }   

        condition.translate(out);
        condition.genLoad("R1", out);

        out.write("Compare_Equal\t R1, 0");
        out.newLine();

        out.write("JumpIfZero\t R1, " + startLabel);
        out.newLine();

        out.write(endLabel + ":");
        out.newLine();
    }
}