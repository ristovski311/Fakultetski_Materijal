namespace Models;

public class Sastojak
{
    [Key]
    public int ID {get;set;}
    public required string Naziv {get;set;}
    public DateTime RokTrajanja {get;set;}
    
    public List<Magacin>? Magacin {get;set;}
}