namespace WebTemplate.Models;

public class DPPotrosac
{
    [Key]
    public int ID {get; set;}
    public required Potrosac Potrosac { get; set; }
    public required DP DP {get; set;}
    public int KorisnickiBroj { get; set; }
    public DateTime DatumPotpisivanjaUgovora { get; set; }
    public int BrojBrojila { get; set; }
}