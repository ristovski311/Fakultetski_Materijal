using System.Text.Json.Serialization;

namespace restorani.Models;

public class Magacin
{
    public int Id { get; set; }
    public Restoran? Restoran { get; set; }
    public Sastojak? Sastojak { get; set; }

    public int Kolicina { get; set; }
}