namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    // DbSet kolekcije!
    public required DbSet<Knjiga> Knjige { get; set; }
    public required DbSet<Korisnik> Korisnici { get; set; }
    public required DbSet<Iznajmljivanje> Iznajmljivanja { get; set; }

    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
