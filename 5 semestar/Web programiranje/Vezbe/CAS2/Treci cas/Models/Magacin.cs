namespace Models;

public class Magacin 
{
    [Key]
    public int ID {get;set;}
    public required Restoran Restoran {get;set;}
    public required Sastojak Sastojak {get;set;}
    public int Kolicina {get;set;}
}