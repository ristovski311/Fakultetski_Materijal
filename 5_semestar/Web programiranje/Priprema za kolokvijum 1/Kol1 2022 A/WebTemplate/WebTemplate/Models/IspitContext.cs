namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    public required DbSet<Aerodrom> Aerodromi {get; set;}
    public required DbSet<Letelica> Letelice {get; set;}
    public required DbSet<Let> Letovi {get; set;}
    public required DbSet<Relacija> Relacije {get; set;}

    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
