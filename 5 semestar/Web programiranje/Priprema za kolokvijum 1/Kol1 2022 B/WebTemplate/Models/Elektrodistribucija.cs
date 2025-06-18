namespace WebTemplate.Models;

public class Elektrodistribucija
{
    [Key]
    public int ID { get; set; }
    [MaxLength(50)]
    public required string Naziv { get; set; }
    public string? Grad { get; set; }
    public string? Email { get; set; }
    public int BrojRadnika { get; set; }
         
}