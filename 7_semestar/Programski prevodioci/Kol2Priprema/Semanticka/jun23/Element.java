public class Element{
    public String name;
    public Constant value;

    public Element(String n)
    {
        this.name = n;
    }

    public Element(String n, Constant c)
    {
        this.name = n;
        this.value = c;
    }
}