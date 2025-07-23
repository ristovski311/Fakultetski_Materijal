namespace WebTemplate.Models;

public class Smer
{
    [Key]
    public int ID { get; set; }
    public required string Naziv { get; set; }
    public DateTime DatumUpisa { get; set; }
    public int ESPB { get; set; }
    public required Fakultet Fakultet { get; set; }
    public required Student Student { get; set; }

}