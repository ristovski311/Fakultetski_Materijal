using Models;

namespace DrugiCas.Models;

public class RestoraniContext : DbContext
{
    public required DbSet<Grad> Gradovi { get; set; }
    public required DbSet<Restoran> Restorani { get; set; }
    public DbSet<TipRestorana> TipRestorana {get;set;}
    public DbSet<Jelo> Jela {get;set;}

    public RestoraniContext(DbContextOptions options) : base(options)
    {
        
    }
}