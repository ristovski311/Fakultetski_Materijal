namespace WebTemplate.Models;

public class Zaposleni
{
    [Key]
    public int ID { get; set;}
    public required string MaticniBroj { get; set; }
    public string? Ime { get; set; } 
    public string? Prezime { get; set; } 
    public DateTime DatumRodjenja { get; set; }
    public string? BrojTelefona {get; set;}
    public List<Ugovor>? Ugovori { get; set; }
}