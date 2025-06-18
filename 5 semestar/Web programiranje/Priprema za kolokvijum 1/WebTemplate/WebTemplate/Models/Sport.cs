using System.Text.Json.Serialization;

namespace WebTemplate.Models;

public class Sport{

    [Key]
    public int ID {get; set;}
    [MaxLength(50)]
    public required string Naziv {get; set;}
    public DateTime PojavioSe {get;set;}
    [JsonIgnore]
    public List<Sportista>? Sportiste { get; set; }

}