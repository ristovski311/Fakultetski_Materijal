namespace WebTemplate.Models;

public class Disciplina
{
    [Key]
    public int ID {get; set;}
    [MaxLength(50)]

    public required string Naziv {get; set;}
    public DateTime DatumOdKadaPostoji {get; set;}
    public int BrojTakmicara {get; set;}
    public string? Opis {get; set;}
    public List<Rekord>? Rekordi {get; set;}

}