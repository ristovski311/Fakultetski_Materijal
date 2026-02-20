public class Break extends Statement
{
    void translate(BufferedWriter out)
    {
        out.write("Jump\tbreakLabel")
    }
}