namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class IspitController : ControllerBase
{
    public IspitContext Context { get; set; }

    public IspitController(IspitContext context)
    {
        Context = context;
    }
    
    [HttpPost("DodavanjeBolnice")]
    public async Task<IActionResult> DodavanjeBolnice([FromBody] Bolnica b)
    {
        try
        {
            await Context.Bolnice.AddAsync(b);
            await Context.SaveChangesAsync();

            return Ok($"Dodata bolnica: {b.Naziv}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodavanjeLekara/{ime}/{prezime}/{datumRodjenja}/{datumDiplomiranja}")]
    public async Task<IActionResult> DodavanjeLekara(string ime, string prezime, DateTime datumRodjenja, DateTime datumDiplomiranja, int? idLicence)
    {
        try
        {
            Licenca? l;
            if(idLicence != null)
            {
                l = await Context.Licence!.FindAsync(idLicence);

                if(l == null)
                    return BadRequest("Ne postoji licenca koja je zadata!");
            }
            else
                l = null;

            Lekar lekar = new Lekar()
            {
                Ime = ime,
                Prezime = prezime,
                DatumRodjenja = datumRodjenja,
                DatumDiplomiranja = datumDiplomiranja,
                Licenca = l
            };

            await Context.Lekari.AddAsync(lekar);
            await Context.SaveChangesAsync();

            return Ok($"Registrovan novi lekar: {lekar.Ime} {lekar.Prezime}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }


    [HttpPost("DodavanjeLekaraBolnici/{idLekara}/{idBolnice}/{datumUgovora}/{specijalnost}")]
    public async Task<IActionResult> DodavanjeLekaraBolnici(int idLekara, int idBolnice, DateTime datumUgovora, string specijalnost)
    {
        try
        {
            Lekar? l = await Context.Lekari.FindAsync(idLekara);

            if(l == null)
                return BadRequest("Ne postoji takav lekar!");

            Bolnica? b = await Context.Bolnice.FindAsync(idBolnice);

            if(b == null)
                return BadRequest("Ne postoji takva bolnica!");

            BolnicaLekar bl = new BolnicaLekar()
            {
                Lekar = l,
                Bolnica = b,
                DatumUgovora = datumUgovora,
                Specijalnost = specijalnost
            };

            await Context.BolnicaLekari.AddAsync(bl);
            await Context.SaveChangesAsync();

            return Ok($"Dodat lekar {l.Ime} {l.Prezime} [{bl.Specijalnost}] u bolnicu {b.Naziv}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("InformacijeOLekaru/{idBolnice}")]
    public async Task<IActionResult> InformacijeOLekaru(int idBolnice)
    {
        try
        {
            var info = await Context.BolnicaLekari.Include(p => p.Lekar!)
                                                        .Where(p=>p.Bolnica!.ID == idBolnice)
                                                        .Select(p => new
                                                        {
                                                            p.Lekar!.Ime,
                                                            p.Lekar!.Prezime,
                                                            p.Lekar!.DatumRodjenja,
                                                            p.Lekar!.DatumDiplomiranja,
                                                            p.Specijalnost
                                                        })
                                                        .ToListAsync();
            return Ok(info);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("BolnicaLekariBezLicence/{idBolnice}")]
    public async Task<IActionResult> BolnicaLekariBezLicence(int idBolnice)
    {
        try
        {
            Bolnica? b = await Context.Bolnice.FindAsync(idBolnice);
            if(b == null)
                return BadRequest("Ne postoji zadata bolnica!");

            var info = await Context.BolnicaLekari.Include(p => p.Lekar!)
                                                        .Where(p=>p.Bolnica!.ID == idBolnice)
                                                        .AnyAsync(p => p.Lekar!.Licenca == null);
            string poruka = "";
            if(info)
                poruka = new string($"Bolnica sa id {idBolnice} ima lekare bez licence!");
            else
                poruka = new string($"Bolnica sa id {idBolnice} nema lekare bez licence!");
            
            return Ok(poruka);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

}
