public class SelectStatement extends Statement
{
    private ArrayList<Expression> conditions;
    private ArrayList<Statement> statements;

    public SelectStatement(ArrayList<Expression> c, ArrayList<Statement> s)
    {
        this.conditions = c;
        this.statements = s;
    }

    void translate() throws IOException
    {
        String endLabel = ASTNode.genLab();
        String nextLabel = ASTNode.genLab();

        for(int i = 0; i < conditions.size(); i++)
        {
            Expression currentCond = conditions.get(i);
            Statement currentSt = statements.get(i);

            currentCond.translate(out);
            currentCond.genLoad("R1",out);

            //Poslednji cond je drugaciji
            if(i == (conditions.size()-1))
            {
                out.write("\tJumpIfZero\tR1, " + endLabel);
                out.newLine();
            }
            else
            {
                out.write("\tJumpIfZero\tR1, " + nextLabel);
                out.newLine();
            }

            currentStatement.translate(out);

            //Poslednji je opet drugaciji jer nema jump na endLab
            if(i != (conditions.size()-1))
            {
                out.write("\tJump\t" + endLabel);
                out.newLine();
                
                out.write(nextLabel + ":");
                out.newLine();

                nextLabel = ASTNode.genLab(); 
            }
        }
    
        out.write(endLabel + ":");
        out.newLine();
    }
}