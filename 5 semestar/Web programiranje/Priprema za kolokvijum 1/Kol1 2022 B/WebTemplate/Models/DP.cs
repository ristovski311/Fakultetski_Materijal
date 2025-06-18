using System.Text.Json.Serialization;

namespace WebTemplate.Models;

public class DP
{
    [Key]
    public int ID { get; set; }
    public string? Naziv {get; set;}

}