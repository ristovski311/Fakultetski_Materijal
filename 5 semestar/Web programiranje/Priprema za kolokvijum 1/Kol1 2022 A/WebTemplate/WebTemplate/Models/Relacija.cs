using System.Text.Json.Serialization;

namespace WebTemplate.Models;

public class Relacija
{
    [Key]
    public int ID { get; set; }

    public required Aerodrom? AerodromOd { get; set; }

    public required Aerodrom? AerodromDo { get; set; }
}