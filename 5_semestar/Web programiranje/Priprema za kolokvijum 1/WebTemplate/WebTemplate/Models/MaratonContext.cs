namespace WebTemplate.Models;

public class MaratonContext : DbContext
{
     public required DbSet<Sportista> Sportisti {get;set;}
    public required DbSet<Sport> Sportovi {get;set;}
    public required DbSet<Rekord> Rekordi {get;set;}
    public required DbSet<Disciplina> Discipline {get;set;}

    public MaratonContext(DbContextOptions o) : base(o)
    {
        
    }
}
//sqllocaldb create ispit -s AKO ZELIMO NOVU DA NAPRAVIMO!
//sqllocaldb info DA VIDIM BAZE