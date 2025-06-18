namespace WebTemplate.Models;

public class Fakultet
{
    [Key]
    public int ID { get; set; }
    public required string Naziv { get; set; }
    public string? Adresa { get; set; }
    public string? BrojTelefona { get; set; }
    public string? Email { get; set; }
    public List<Smer>? Smerovi { get; set; }
}