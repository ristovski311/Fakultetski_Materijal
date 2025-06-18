using Models;

namespace DrugiCas.Models;

public class Restoran
{
    [Key]
    public int ID { get; set; }
    
    public required string Naziv {get; set;}

    public double X {get; set;}
    public double Y {get; set;}

    //tip hrane - kataloski tip ili string polje kakav je taj tip
    //mana ako se italijanski pise na razlicite nacine
    //kataloska tabela- naziv i id

    public TipRestorana? /*? moze da bude null u bazi, a i objekat moze null*/ Tip {get;set;}

    //za prosecnu ocenu mozemo novu klasu koja cuva ocene i id, mi cemo dva property-ja

    public int UkupnaSumaOcena {get;set;}
    public int BrojOcenjivanja {get;set;}

    public Grad? Grad { get; set; }

    public List<Jelo>? Meni {get;set;}
    public List<Magacin>? Magacin {get;set;}
}