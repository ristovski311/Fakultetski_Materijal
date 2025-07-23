namespace DrugiCas.Models;

public class Restoran
{
    [Key]
    public int ID { get; set; }

    public Grad? Grad { get; set; }
}