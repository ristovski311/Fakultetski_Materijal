namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    // DbSet kolekcije!

    public DbSet<Potrosac>? Potrosaci { get; set; }
    public DbSet<DP>? DPovi { get; set; }
    public DbSet<DPPotrosac>? Ugovori { get; set; }
    public DbSet<Elektrodistribucija>? Elektrodistribucije { get; set; }


    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
