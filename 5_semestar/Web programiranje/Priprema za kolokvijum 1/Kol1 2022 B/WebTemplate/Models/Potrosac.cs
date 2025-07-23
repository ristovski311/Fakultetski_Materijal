using System.Text.Json.Serialization;

namespace WebTemplate.Models;

public class Potrosac
{
    [Key]
    public int ID { get; set; }
    [JsonIgnore]
    public List<DPPotrosac>? DPovi { get; set; }
    public string? Ime {get; set; }
    public string? Prezime {get; set;}
    public int GodinaRodjenja {get; set;}
    public string? MestoRodjenja {get; set;} 
}