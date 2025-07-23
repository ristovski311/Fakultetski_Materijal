using System.Text.Json.Serialization;

namespace WebTemplate.Models;

public class Let
{
    [Key]
    public int ID { get; set; }
    public required Relacija Relacija { get; set; }
    public Letelica? Letelica { get; set; }
    public int BrojPutnika { get; set; }
    public DateTime VremePoletanja {get; set;}
    public DateTime VremeSletanja {get; set;}
}