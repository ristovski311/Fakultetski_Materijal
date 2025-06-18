namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    public required DbSet<Knjiga> Knjige { get; set; }
    public required DbSet<Autor> Autori { get; set; }
    public required DbSet<IzdavackaKuca> IzdavackeKuce { get; set; }
    public required DbSet<Ugovor> Ugovori { get; set; }
    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
