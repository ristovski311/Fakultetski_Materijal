namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    public required DbSet<Proizvod> Proizvodi { get; set; }
    public required DbSet<Prodavnica> Prodavnice { get; set; }
    public required DbSet<Artikal> Artikli { get; set; }
    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
