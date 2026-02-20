public class TypeAndDim{

    public int dim;
    public String type;

    public TypeAndDim(int dim)
    {
        this.dim = dim;
    }

    public TypeAndDim(String type)
    {
        this.type = type
    }

    public TypeAndDim(String t, int d)
    {
        this.dim = d;
        this.type = t;
    }
}