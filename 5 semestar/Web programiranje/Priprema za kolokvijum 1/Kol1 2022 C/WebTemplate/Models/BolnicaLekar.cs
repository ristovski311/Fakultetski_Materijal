namespace WebTemplate.Models;

public class BolnicaLekar
{
    [Key]
    public int ID { get; set; }
    public Lekar? Lekar { get; set; }
    public Bolnica? Bolnica {get; set;}
    public DateTime DatumUgovora { get; set; }
    public string? Specijalnost {get; set;}
}