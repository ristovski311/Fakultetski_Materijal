namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    // DbSet kolekcije!

    public DbSet<Smer>? Smerovi { get; set; }
    public DbSet<Fakultet>? Fakulteti { get; set; }
    public DbSet<Student>? Studenti { get; set; }


    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
