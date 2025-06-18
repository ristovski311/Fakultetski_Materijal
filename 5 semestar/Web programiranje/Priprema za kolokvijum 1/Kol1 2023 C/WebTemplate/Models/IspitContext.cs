namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    // DbSet kolekcije!
    public required DbSet<Ustanova> Ustanove { get; set; }
    public required DbSet<Zaposleni> Zaposleni { get; set; }
    public required DbSet<Ugovor> Ugovori { get; set; }


    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
