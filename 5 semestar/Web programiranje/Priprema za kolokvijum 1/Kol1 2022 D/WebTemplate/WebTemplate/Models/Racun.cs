namespace WebTemplate.Models;

public class Racun
{
    [Key]
    public int ID { get; set; }
    public required Klijent Klijent { get; set; }
    public required Banka Banka { get; set; }
    public required string BrojRacuna { get; set; }
    public DateTime DatumOtvaranja { get; set; }
    public double Sredstva { get; set; }
    public double UkupanPodignutNovac { get; set; }
}