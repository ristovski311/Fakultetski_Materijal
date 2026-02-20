public class SelectExpression extends Expression
{
    public Expression selection;
    public ArrayList<Expression> options;

    public Expression(Expression s, ArrayList<Expression> list)
    {
        this.selection = s;
        this.options = list;
    }

    void translate(BufferedWriter out) throws IOException
    {
        String labelEnd = ASTNode.genLab();
        String labelNext;
        if(options != null && options.size != 0)
            labelNext = ASTNode.genLab();
        else
            labelNext = labelEnd;

        //Prvo uslov odredjivanja
        selection.translate(out);
        selection.genLoad("R1", out);

        if(options != null)
        {
            for(int i = 0; i < options.size; i++)
            {

                out.write("\tLoad_Const\tR2, " + i);
                out.newLine();

                out.write("\tCompare_Equal\tR2, R1");
                out.newLine();

                Expression currentOption = options.get(i);
                if(i < options.size - 1) 
                {
                    out.write("\tJumpIfZero\tR2, " + labelNext);
                    out.newLine();
                    currentOption.translate(out);
                    currentOption.genLoad("R3", out);
                    //Kako poslednji nece imati labelEnd, moramo selektivno ispisivati ovaj deo
                    out.write("\tJump\t" + labelEnd);
                    out.newLine();
                    //Svi osim poslednjeg takodje ispod sebe imaju labelNext ispisan
                    out.write(labelNext + ":");
                    out.newLine();
                }
                else
                {
                    out.write("\tJumpIfZero\tR2, " + labelEnd);
                    out.newLine();
                    currentOption.translate(out);
                }
            }

            labelNext = ASTNode.genLab();
        }

        //Konacna labela
        out.write(labelEnd + ":");
        out.newLine();

        super.result = ASTNode.genVar();
        out.write("\tStore\tR3, " + super.result);
        out.newLine();
    }
}