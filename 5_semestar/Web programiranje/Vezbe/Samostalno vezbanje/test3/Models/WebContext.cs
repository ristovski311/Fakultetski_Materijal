using Microsoft.EntityFrameworkCore;

namespace test3.Models;

public class WebContext : DbContext
{
    public WebContext(DbContextOptions o) : base(o) {}

    public DbSet<Grad> Grad {get;set;}
}