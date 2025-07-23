namespace WebTemplate.Models;

public class Banka
{
    [Key]
    public int ID { get; set; }
    [MaxLength(50)]
    public required string Naziv { get; set; }
    [MaxLength(50)]
    public string? Lokacija { get; set; }
    public string? BrojTelefona { get; set; }
    public int BrojZaposlenih { get; set; }
    public List<Racun>? Racuni {get; set;}
}