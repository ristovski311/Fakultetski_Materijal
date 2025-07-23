namespace restorani.Models;

public class RestoraniContext : DbContext
{
    public required DbSet<Grad> Gradovi { get; set; }
    public required DbSet<Restoran> Restorani { get; set; }
    public required DbSet<TipRestorana> TipRestorana { get; set; }
    public required DbSet<Jelo> Jela { get; set; }
    // Dodato radi lakseg dodavanja sastojka magacinu
    public required DbSet<JeloSastojak> Recept { get; set; }
    public required DbSet<Magacin> MagaciniRestorana { get; set; }
    public required DbSet<Sastojak> Sastojci { get; set; }

    public RestoraniContext(DbContextOptions options) : base(options)
    {

    }
}