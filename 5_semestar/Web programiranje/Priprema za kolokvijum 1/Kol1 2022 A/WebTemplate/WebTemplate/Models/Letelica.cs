namespace WebTemplate.Models;

public class Letelica
{
    [Key]
    public int ID { get; set; }
    [MaxLength(50)]
    public required string Naziv { get; set; }
    public int KapacitetPutnika { get; set; }
    public int BrojOsoblja { get; set; }
    public int BrojMotora {get; set;}

}