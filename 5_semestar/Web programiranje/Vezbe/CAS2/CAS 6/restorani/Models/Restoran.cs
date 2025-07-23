using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace restorani.Models;

public class Restoran
{
    [Key]
    public int ID { get; set; }

    public required string Naziv { get; set; }

    public double X { get; set; }
    public double Y { get; set; }

    public TipRestorana? Tip { get; set; }

    public int UkupnaSumaOcena { get; set; }

    public int BrojOcenjivanja { get; set; }

    [NotMapped]
    public double ProsecnaOcena
    {
        get
        {
            /*if (BrojOcenjivanja == 0)
            {
                return (double)UkupnaSumaOcena / 1;
            }
            else
            {
                return (double)UkupnaSumaOcena / BrojOcenjivanja;
            }*/
            return (double)UkupnaSumaOcena /
                (BrojOcenjivanja == 0 ? 1 : BrojOcenjivanja);
        } 
    }

    [JsonIgnore]
    public Grad? Grad { get; set; }

    public List<Jelo>? Meni { get; set; }

    public List<Magacin>? Magacin { get; set; }

    public double Prihodi { get; set; }

    public double Rashodi { get; set; }

    [NotMapped]
    public double Zarada
    {
        get
        {
            return Prihodi - Rashodi;
        }
    }
}