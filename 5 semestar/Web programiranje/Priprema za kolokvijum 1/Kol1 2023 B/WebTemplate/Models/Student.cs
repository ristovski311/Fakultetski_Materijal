namespace WebTemplate.Models;
public class Student
{
    [Key]
    public int ID { get; set; }
    public int Indeks { get; set; }
    public required string Ime { get; set; }
    public required string Prezime { get; set; }
    public int GodinaRodjenja { get; set; }
    public string? ZavrsenaSrednjaSkola { get; set; }
}