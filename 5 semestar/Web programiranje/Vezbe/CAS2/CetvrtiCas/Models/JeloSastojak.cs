namespace Models;

public class JeloSastojak
{
    [Key]
    public int ID{get;set;}
    public required Jelo Jelo {get;set;}
    public required Sastojak Sastojak {get;set;}
    public int Kolicina {get;set;}

}