public class Par{
    public String id;
    public Constant val_const;
    public ArrayList<Par> val_list;
    public String val_id;

    public Par(String id, Constant c)
    {
        this.id = id;
        this.val_const = c;
    }

    public Par(String id, ArrayList<Par> list)
    {
        this.id = id;
        this.val_list = list;
    }

    public Par(String id, String id2)
    {
        this.id = id;
        this.val_id = id2;
    }
}