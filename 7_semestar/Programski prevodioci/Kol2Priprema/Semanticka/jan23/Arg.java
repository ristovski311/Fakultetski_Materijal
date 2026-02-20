public class Arg{
    public Type type;
    public String name;
    public Constant value;

    public Arg(String n, Constant v, Type t)
    {
        this.name = n;
        this.value = v;
        this.type = t;
    }

    public Arg(String n)
    {
        this.name = n;
    }

    public Arg(String n, Type t)
    {
        this.name = n;
        this.type = t;
    }

}