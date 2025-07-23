using Microsoft.EntityFrameworkCore;

namespace test2.Models;

public class WebContext:DbContext
{
    public WebContext(DbContextOptions d) : base(d)
    {}

    public DbSet<Grad> Grad {get; set;}
}