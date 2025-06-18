namespace WebTemplate.Models;

public class Aerodrom
{
    [Key]
    public int ID { get; set; }
    [MaxLength(50)]
    public required string Naziv { get; set; }
    [MaxLength(3)]
    public required string Kod { get; set; }
    [MaxLength(50)]
    public required string  Lokacija { get; set; }
    public int KapacitetLetelica { get; set; }
    public int KapacitetPutnika { get; set; }

}