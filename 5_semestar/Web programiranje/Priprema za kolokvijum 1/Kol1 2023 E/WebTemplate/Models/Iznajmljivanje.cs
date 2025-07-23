namespace WebTemplate.Models;

public class Iznajmljivanje
{
    [Key]
    public int ID { get; set; }
    public DateTime DatumIznajmljivanja { get; set; }
    public int RokZaVracanje { get; set; }
    public required Korisnik Korisnik { get; set; }
    public required Knjiga Knjiga { get; set; }
}