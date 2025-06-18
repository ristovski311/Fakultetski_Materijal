namespace WebTemplate.Models;

public class Bolnica
{
    [Key]
    public int ID { get; set; }
    [MaxLength(50)]
    public required string Naziv { get; set; }
    public string? Lokacija { get; set; }
    public int BrojOdeljenja { get; set; }
    public int BrojOsoblja { get; set; }
    public string? BrojTelefona { get; set; }
    public List<BolnicaLekar>? Lekari { get; set; }
}