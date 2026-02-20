public class Arg{

    Type type;
    Constant value;
    String name;

    public Arg(Type t, Constant c, String n)
    {
        this.type = t;
        this.value = c;
        this.name = n;

    }

    public Arg(Type t)
    {
        this.type = t;
        this.value = null;
    }

    public Arg(String n, Type t)
    {
        this.type = t;
        this.name = n;
    }
}