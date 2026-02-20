public class DoWhileStatement extends Statement 
{
    public ArrayList<Statement> block;
    public Expression condition;
    
    //OVO RESENJE NE RADI ZA UGNJEZDENE PETLJE
    //Radio sam pre nego sto sam uradio Oktobar 2 2019
    //Nisam znao da moze da se radi sa instanceof operatorom
    //Izmenjeno resenje u drugom folderu

    public DoWhileStatement(ArrayList<Statement> b, Expression c)
    {
        this.block = b;
        this.condition = c;
    }

    void translate(BufferedWriter out) throws IOException
    {
        String startLabel = ASTNode.genLab();
        String endLabel = ASTNode.genLab();
        String breakLabel = "breakLabel";
        String continueLabel = "continueLabel"; 
    
        out.write(continueLabel + ":");
        out.newLine();

        //Napomena: Nije neophodno da imamo i start i continueLabel
        //Moze samo jedan da se koristi, isto i sa break i endLabel,
        //Ali je ovako lakse da se vidi sta se zapravo desava
        out.write(startLabel + ":");
        out.newLine;

        for(Statement s : block)
        {
            s.translate(out);
        }   

        condition.translate(out);
        condition.genLoad("R1", out);

        out.write("Compare_Equal\t R1, 0");
        out.newLine();

        out.write("JumpIfZero\t R1, " + startLabel);
        out.newLine();

        out.write(breakLabel + ":");
        out.newLine();

        out.write(endLabel + ":");
        out.newLine();


    }
}