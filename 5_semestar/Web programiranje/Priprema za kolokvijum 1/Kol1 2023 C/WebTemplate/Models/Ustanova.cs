namespace WebTemplate.Models;

public class Ustanova
{
    [Key]
    public int ID { get; set; }
    public required string Naziv { get; set; }
    public string? Adresa { get; set; }
    public string? BrojTelefona { get; set; }
    public string? Email { get; set; }
    public List<Ugovor>? Ugovori { get; set; }

}