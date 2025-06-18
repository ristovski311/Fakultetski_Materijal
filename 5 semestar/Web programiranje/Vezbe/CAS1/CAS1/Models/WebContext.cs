

namespace CAS1.Models;

public class WebContext:DbContext
{
    public WebContext(DbContextOptions options) :base(options)
    {

    }
    public DbSet<Grad> Grad {get; set;}
}