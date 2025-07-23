namespace restorani.Models;

public class Jelo
{

    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public string? Slika { get; set; }

    public int? KalorijskaVrednost { get; set; }

    public bool DaLiJeJelo { get; set; }

    public Restoran? Restoran { get; set; }

    public List<JeloSastojak>? Sastojci { get; set; }

}