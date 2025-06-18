namespace WebTemplate.Models;

public class Proizvod
{
    [Key]
    public int ID { get; set; }
    public required string Naziv { get; set; }
    [MaxLength(13)]
    public string? Identifikator { get; set; }
    public DateTime DatumProizvodnje { get; set; }
    public DateTime RokTrajanja { get; set; }
}