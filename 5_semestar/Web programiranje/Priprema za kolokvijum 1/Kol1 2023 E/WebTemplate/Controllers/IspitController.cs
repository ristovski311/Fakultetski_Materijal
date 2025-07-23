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
    
    [HttpPost("DodavanjeKorisnika")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> DodavanjeKorisnika([FromBody] Korisnik k)
    {
        try
        {
            if(string.IsNullOrWhiteSpace(k.Ime))
                return BadRequest("Ime je obavezno!");
                
            if(string.IsNullOrWhiteSpace(k.Prezime))
                return BadRequest("Prezime je obavezno!");

            if((await Context.Korisnici.Where(p => p.Identifikator == k.Identifikator).FirstOrDefaultAsync()) != null)
                return BadRequest("Vec postoji korisnik s datim Identifikatorom biblioteke!");

            await Context.Korisnici.AddAsync(k);
            await Context.SaveChangesAsync();

            return Ok($"Uspesno dodat korisnik {k.Ime} {k.Prezime}");

        }
        catch(Exception e)
        {
            return BadRequest(new {
                Error = e.Message,
                Inner = e.InnerException!.Message
            });
        }
    }

    [HttpPost("DodavanjeKnjige")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> DodavanjeKnjige([FromBody] Knjiga k)
    {
        try
        {
            if(string.IsNullOrWhiteSpace(k.Naslov))
                return BadRequest("Naslov je obavezan!");
                
            if(string.IsNullOrWhiteSpace(k.Autor))
                return BadRequest("Autor polje je obavezno!");

            if((await Context.Knjige.Where(p => p.Naslov == k.Naslov && p.Autor == k.Autor).FirstOrDefaultAsync()) != null)
                return BadRequest("Vec postoji kjiga s datim naslovom i autorom!");

            await Context.Knjige.AddAsync(k);
            await Context.SaveChangesAsync();

            return Ok($"Uspesno dodata knjiga {k.Naslov} / {k.Autor}");

        }
        catch(Exception e)
        {
            return BadRequest(new {
                Error = e.Message,
                Inner = e.InnerException!.Message
            });
        }
    }

    [HttpPost("Iznajmljivanje")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> Iznajmljivanje([FromBody] Iznajmi i)
    {
        try
        {
            Korisnik? k = await Context.Korisnici.FindAsync(i.korisnikId);
            Knjiga? knj = await Context.Knjige.FindAsync(i.knjigaId);

            if(k == null)
                return BadRequest("Ne postoji proslednjeni korisnik!");

                
            if(knj == null)
                return BadRequest("Ne postoji proslednjena knjiga!");

            if(knj.BrojDostupnihPrimeraka == 0)
                return BadRequest("Nema dostupnih primeraka!");

            if(k.BrojIznajmljenihKnjiga == 5)
                return BadRequest("Korisnik ne moze iznamiti preko 5 knjiga istovremeno!");

            Iznajmljivanje iz = new Iznajmljivanje()
            {
                Korisnik = k,
                Knjiga = knj,
                DatumIznajmljivanja = i.datumIznajmljivanja,
                RokZaVracanje = i.RokZaVracanje
            };

            k.BrojIznajmljenihKnjiga++;
            Context.Korisnici.Update(k);

            knj.BrojDostupnihPrimeraka--;
            Context.Knjige.Update(knj);

            await Context.Iznajmljivanja.AddAsync(iz);
            await Context.SaveChangesAsync();

            return Ok($"Korisnik {k.Ime} {k.Prezime} je iznajmio knjigu {knj.Naslov} / {knj.Autor}.\nTrenutno ima ukupno {k.BrojIznajmljenihKnjiga} iznamljenih knjiga!");

        }
        catch(Exception e)
        {
            return BadRequest(new {
                Error = e.Message,
                Inner = e.InnerException!.Message
            });
        }
    }


    [HttpPut("Vrati/{idKorisnika}/{idKnjige}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> Vrati(int idKorisnika, int idKnjige)
    {
        try
        {
            Korisnik? k = await Context.Korisnici.FindAsync(idKorisnika);
            Knjiga? knj = await Context.Knjige.FindAsync(idKnjige);

            if(k == null)
                return BadRequest("Ne postoji proslednjeni korisnik!");

                
            if(knj == null)
                return BadRequest("Ne postoji proslednjena knjiga!");   
            Iznajmljivanje? iz;
            if((iz = await Context.Iznajmljivanja.Where(p => p.Korisnik == k && p.Knjiga == knj).FirstOrDefaultAsync()) == null)
                return BadRequest("Korisnik nije iznajmio tu knjigu!");

            knj.BrojDostupnihPrimeraka++;
            k.BrojIznajmljenihKnjiga--;
            Context.Iznajmljivanja.Remove(iz);
            Context.Korisnici.Update(k);
            Context.Knjige.Update(knj);
            await Context.SaveChangesAsync();
            
            return Ok($"Knjigu {knj.Naslov} / {knj.Autor} je vratio {k.Ime} {k.Prezime}!");

        }
        catch(Exception e)
        {
            return BadRequest(new {
                Error = e.Message,
                Inner = e.InnerException!.Message
            });
        }
    }

    [HttpGet("NisuVratili")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> NisuVratili()
    {
        try
        {
            DateTime now = DateTime.Now;

            var info = Context.Iznajmljivanja.Include(p => p.Korisnik)
                                            .Where(p => p.DatumIznajmljivanja.AddDays(p.RokZaVracanje) < now)
                                            .Select(p => new
                                            {
                                                Ime = p.Korisnik.Ime,
                                                Prezime = p.Korisnik.Prezime,
                                                Id = p.Korisnik.Identifikator,
                                            }).Distinct();
            
            return Ok(info);

        }
        catch(Exception e)
        {
            return BadRequest(new {
                Error = e.Message,
                Inner = e.InnerException!.Message
            });
        }
    }

    [HttpGet("ManjeOdPetKnjiga")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> ManjeOdPetKnjiga()
    {
        try
        {

            var info = Context.Knjige.Where(p => p.BrojDostupnihPrimeraka < 5)
                                    .Select(p => new
                                    {
                                        Naslov = p.Naslov,
                                        Autor = p.Autor,
                                        Broj = p.BrojDostupnihPrimeraka,
                                        Zanr = p.Zanr
                                    }).Distinct();
            
            return Ok(info);

        }
        catch(Exception e)
        {
            return BadRequest(new {
                Error = e.Message,
                Inner = e.InnerException!.Message
            });
        }
    }
}
