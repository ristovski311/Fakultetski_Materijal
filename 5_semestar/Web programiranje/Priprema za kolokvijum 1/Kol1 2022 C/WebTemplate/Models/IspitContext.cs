namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    // DbSet kolekcije!
    public required DbSet<Bolnica> Bolnice { get; set; }
    public required DbSet<BolnicaLekar> BolnicaLekari { get; set; }
    public required DbSet<Lekar> Lekari { get; set; }
    public required DbSet<Licenca> Licence { get; set; }

    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
