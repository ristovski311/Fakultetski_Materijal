namespace WebTemplate.Models;

public class Knjiga
{
    [Key]
    public int ID { get; set; }
    public required string Naslov { get; set; }
    public DateTime? DatumObjavljivanja { get; set; }
    public int BrojStranica { get; set; }
    public string? Zanr { get; set; }
    public string? ISBN { get; set; }
    public Autor? Autor { get; set; }
}