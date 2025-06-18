namespace DrugiCas.Models;

public class Grad
{
    [Key]
    public int ID { get; set; }
    public required string Naziv { get; set; }
    public double Povrsina { get; set; }
    public int BrojStanovnika { get; set; }

    public List<Restoran>? Restorani { get; set; }
}