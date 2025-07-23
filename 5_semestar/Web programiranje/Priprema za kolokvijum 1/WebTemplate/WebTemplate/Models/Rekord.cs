namespace WebTemplate.Models;

public class Rekord
{
    [Key]
    public int ID {get;set;}
    public required string Takmicenje {get; set;}
    public DateTime OstvarenDana {get; set;}
    public Sportista? Sportista {get; set;}
    public Disciplina? Disciplina {get; set;}
}