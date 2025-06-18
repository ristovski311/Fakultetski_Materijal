namespace restorani.Models;

public class JeloSastojak
{
    public int ID { get; set; }

    public required Jelo Jelo { get; set; }

    public required Sastojak Sastojak { get; set; }

    public int Kolicina { get; set; }
}