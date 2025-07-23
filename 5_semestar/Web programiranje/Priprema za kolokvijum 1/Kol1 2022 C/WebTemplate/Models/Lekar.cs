using System.Text.Json.Serialization;

namespace WebTemplate.Models;

public class Lekar
{
    [Key]
    public int ID { get; set; }
    [JsonIgnore]
    public List<BolnicaLekar>? Bolnice { get; set; }
    public required string Ime { get; set; }
    public required string Prezime { get; set; }
    public DateTime DatumRodjenja { get; set; }
    public DateTime DatumDiplomiranja { get; set; }
    public Licenca? Licenca { get; set; }

}