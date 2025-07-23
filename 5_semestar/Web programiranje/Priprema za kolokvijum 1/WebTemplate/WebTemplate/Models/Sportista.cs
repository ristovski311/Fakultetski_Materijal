using System.Text.Json.Serialization;

namespace WebTemplate.Models;

public class Sportista
{
    [Key]
    public int ID {get; set;}
    [MaxLength(50)]
    public required string Ime { get; set; }
    
    [MaxLength(50)]
    public required string Prezime { get; set; }
    public char Pol {get;set;}
    public DateTime DatumRodjenja {get; set;}
    public List<Sport>? Sportovi {get; set;}

    public List<Rekord>? Rekordi {get; set;}
}