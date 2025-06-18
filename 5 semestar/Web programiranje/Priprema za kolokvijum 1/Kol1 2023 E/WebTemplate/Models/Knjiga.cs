namespace WebTemplate.Models;

public class Knjiga
{
    [Key]
    public int ID { get; set; }
    public required string Naslov { get; set; }
    public DateTime DatumIzdavanja { get; set; }
    public required string Autor { get; set; }
    public required string Zanr { get; set; }
    public int BrojDostupnihPrimeraka { get; set; }
    public List<Iznajmljivanje>? Iznajmljivanja {get; set;} 
}