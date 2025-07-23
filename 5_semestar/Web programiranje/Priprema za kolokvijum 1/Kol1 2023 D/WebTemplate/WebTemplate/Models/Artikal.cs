namespace WebTemplate.Models;

public class Artikal
{
    [Key]
    public int ID { get; set; }
    public double Cena { get; set; }
    public required Proizvod Proizvod { get; set; }
    public required Prodavnica Prodavnica { get; set; }
    public int Kolicina { get; set; }
}