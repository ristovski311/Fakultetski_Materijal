namespace restorani.Models;

public class Sastojak
{
    [Key]
    public int ID { get; set; }
    public required string Naziv { get; set; }

    // Dodato za potrebe racunanja cene pripremljenog jela u kuhinji
    public double Cena { get; set; }
    public DateTime RokTrajanja { get; set; }
    public List<Magacin>? Magacin { get; set; }
}
