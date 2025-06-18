namespace WebTemplate.Models;

public class Ugovor
{
    [Key]
    public int ID { get; set; }
    public int BrojUgovora { get; set; }
    public DateTime DatumPotpisa { get; set; }
    public required Zaposleni Zaposleni { get; set; }
    public required Ustanova Ustanova { get; set; }
}