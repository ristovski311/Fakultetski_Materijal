namespace WebTemplate.Models;

public class IzdavackaKuca
{
    [Key]
    public int ID { get; set; }
    public required string Naziv { get; set; }
    public required string Drzava { get; set; }

}