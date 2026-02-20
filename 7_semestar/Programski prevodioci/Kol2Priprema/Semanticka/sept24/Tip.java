public class Tip
{
    public String name;
    public ArrayList<Tip> list;

    public Tip(String name)
    {
        this.name = name;
    }

    public Tip(String name, ArrayList<Tip> l)
    {
        this.name = name;
        this.list = l;
    }
}
