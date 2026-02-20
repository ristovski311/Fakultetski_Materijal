public class Continue extends Statement
{
    private String continueLab;

    public Continue(String b)
    {
        this.continueLab = b;
    }

    public setContinueLab(String l)
    {
        this.continueLab = l;
    }

    void translate(BufferedWriter out)
    {
        out.write("Jump\t" + continueLab);
    }
}