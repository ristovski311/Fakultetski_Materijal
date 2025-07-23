namespace WebTemplate.Models;

public class Ugovor
{
    [Key]
    public int ID { get; set; }
    public Knjiga? Knjiga { get; set; }
    public Autor? Autor {get; set;}
    public DateTime DatumPotpisa { get; set; }
    public IzdavackaKuca? IzdavackaKuca { get; set; }
}