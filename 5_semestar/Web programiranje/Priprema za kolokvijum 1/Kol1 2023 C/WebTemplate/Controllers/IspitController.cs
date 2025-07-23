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
    
    [HttpPost("DodavanjeZaposlenog")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> DodavanjeZaposlenog([FromBody] Zaposleni z)
    {
        try
        {
            if(string.IsNullOrWhiteSpace(z.Ime))
                return BadRequest("Ime je obavezno!");
                
            if(string.IsNullOrWhiteSpace(z.Prezime))
                return BadRequest("Prezime je obavezno!");

            
            if((await Context.Zaposleni.Where(p => p.MaticniBroj == z.MaticniBroj).FirstOrDefaultAsync()) != null)
                return BadRequest("Vec postoji zaposleni s tim maticnim brojem!");

            await Context.Zaposleni.AddAsync(z);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat zaposleni: {z.Ime} {z.Prezime}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.InnerException);
        }
    }

    [HttpPost("DodavanjeUstanove")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> DodavanjeUstanove([FromBody] Ustanova u)
    {
        try
        {
            if(string.IsNullOrWhiteSpace(u.Naziv))
                return BadRequest("Naziv je obavezan!");
                                  
            await Context.Ustanove.AddAsync(u);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata ustanova: {u.Naziv}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.InnerException);
        }
    }

    [HttpPost("AngazovanjeZaposlenog")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> AngazovanjeZaposlenog([FromBody] Angazovanje a)
    {
        try
        {
            Zaposleni? z = await Context.Zaposleni.FindAsync(a.zaposleniId); 
            Ustanova? u = await Context.Ustanove.FindAsync(a.UstanovaId); 

            if(z == null)
                return BadRequest("Ne postoji proslednjeni zaposleni!");
                
            if(u == null)
                return BadRequest("Ne postoji prosledjena ustanova!");
                                  
            if((await Context.Ugovori.Where(p => p.Zaposleni == z && p.Ustanova == u).FirstOrDefaultAsync())!= null)
                return BadRequest($"Ugovor izmedju zaposlenog {z.Ime} {z.Prezime} i ustanove {u.Naziv} vec postoji!");

            Ugovor ug = new Ugovor()
            {
                Zaposleni= z,
                Ustanova = u,
                DatumPotpisa = a.datumPotpisa,
                BrojUgovora = a.BrojUgovora
            };

            await Context.Ugovori.AddAsync(ug);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat ugovor izmedju zaposlenog {z.Ime} {z.Prezime} i ustanove {u.Naziv}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.InnerException);
        }
    }


    [HttpPut("IzmenaAngazovanja/{idZaposlenog}/{idUstanova}/{novBroj}/{novDatumPotpisa}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> IzmenaAngazovanja(int idZaposlenog, int idUstanova, int novBroj, DateTime novDatumPotpisa)
    {
        try
        {
            Zaposleni? z = await Context.Zaposleni.FindAsync(idZaposlenog); 
            Ustanova? u = await Context.Ustanove.FindAsync(idUstanova); 

            if(z == null)
                return BadRequest("Ne postoji proslednjeni zaposleni!");
                
            if(u == null)
                return BadRequest("Ne postoji prosledjena ustanova!");

            Ugovor? ug;

            if((ug = await Context.Ugovori.Where(p => p.Zaposleni == z && p.Ustanova == u).FirstOrDefaultAsync())== null)
                return BadRequest($"Ugovor izmedju zaposlenog {z.Ime} {z.Prezime} i ustanove {u.Naziv} ne postoji!");
            
            ug.BrojUgovora = novBroj;
            ug.DatumPotpisa = novDatumPotpisa;

            Context.Ugovori.Update(ug);
            await Context.SaveChangesAsync();
                        
            return Ok($"Uspesno izmenjen ugovor izmedju zaposlenog {z.Ime} {z.Prezime} i ustanove {u.Naziv}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.InnerException);
        }
    }

    [HttpGet("PronalazakZaposlenih/{danPocetka}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> PronalazakZaposlenih(DateTime danPocetka)
    {
        try
        {
            var info = Context.Ugovori.Include(p => p.Zaposleni)
                                            .Where(p =>p.DatumPotpisa >= danPocetka)
                                            .GroupBy(p => p.Zaposleni)
                                            .Where(g => g.Select(g => g.Ustanova).Distinct().Count() > 1)
                                            .Select(p => p.Key)
                                            .Select(p => new{
                                                p.Ime,
                                                p.Prezime,
                                                p.BrojTelefona
                                            });
            return Ok(info);
        }
        catch(Exception e)
        {
            return BadRequest(e.InnerException);
        }
    }

    [HttpGet("UkupnoRadnihDana")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<IActionResult> UkupnoRadnihDana()
    {
        try
        {
            DateTime now = DateTime.Now;
            var info = Context.Ugovori.Select(p => p.DatumPotpisa);
            var sum = 0.0;
            foreach(var v in info)
                sum += (now - v).TotalDays;
            return Ok(sum);
        }
        catch(Exception e)
        {
            var errorDetails = new
        {
            ErrorMessage = e.Message,
            InnerException = e.InnerException?.Message,
            StackTrace = e.StackTrace
        };
            return BadRequest(errorDetails);
        }
    }

}
