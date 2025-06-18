namespace WebTemplate.Models;

public class Korisnik
{
    [Key]
    public int ID { get; set; }
    public int Identifikator { get; set; }
    public required string Ime { get; set; }
    public required string Prezime { get; set; }
    public DateTime DatumRodjenja { get; set; }
    public char Pol { get; set; }
    public int BrojIznajmljenihKnjiga { get; set; }
    public List<Iznajmljivanje>? Iznajmljivanja { get; set; }
}