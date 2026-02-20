public class Break extends Statement
{
    private String breakLab;

    public Break(String b)
    {
        this.breakLab = b;
    }

    public setBreakLab(String l)
    {
        this.breakLab = l;
    }

    void translate(BufferedWriter out)
    {
        out.write("Jump\t" + breakLab);
    }
}