namespace WebTemplate.Models;

public class Prodavnica
{
    [Key]
    public int ID { get; set; }
    public required string Naziv { get; set; }
    public string? Adresa { get; set; }
    public string? BrojTelefona { get; set; }
    public string? ImeZaduzenogLica { get; set; }
    public List<Artikal>? Artikli { get; set; }

}