public class Continue extends Statement
{
    void translate(BufferedWriter out)
    {
        out.write("Jump\tcontinueLabel");
        out.newLine();
    }
}