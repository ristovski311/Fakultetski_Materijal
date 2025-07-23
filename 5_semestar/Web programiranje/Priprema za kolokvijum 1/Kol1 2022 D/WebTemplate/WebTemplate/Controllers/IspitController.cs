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

    [HttpPost("DodajBanku")]
    public async Task<IActionResult> DodajBanku([FromBody] Banka b)
    {
        try
        {
            await Context.Banke.AddAsync(b);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodata banka: {b.Naziv}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodajKlijenta")]
    public async Task<IActionResult> DodajKlijenta([FromBody] Klijent k)
    {
        try
        {
            await Context.Klijenti.AddAsync(k);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat klijent: {k.Ime} {k.Prezime}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodajRacun/{idKlijenta}/{idBanke}/{brRacuna}/{datumOtvaranja}")]
    public async Task<IActionResult> DodajRacun(int idKlijenta, int idBanke, string brRacuna, DateTime datumOtvaranja)
    {
        try
        {
            Banka? b = await Context.Banke.FindAsync(idBanke);
            Klijent? k = await Context.Klijenti.FindAsync(idKlijenta);

            if(k == null)
                return BadRequest("Klijent ne postoji!");
                
            if(b == null)
                return BadRequest("Banka ne postoji!");

            Racun r = new Racun()
            {
                Klijent = k,
                Banka = b,
                Sredstva = 0,
                UkupanPodignutNovac = 0,
                BrojRacuna = brRacuna,
                DatumOtvaranja = datumOtvaranja
            };

            await Context.Racuni.AddAsync(r);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat racun: {k.Ime} {k.Prezime} -> {b.Naziv} [{r.BrojRacuna}]");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

     [HttpPut("PromeniStanje/{idKlijenta}/{brRacuna}/{novoStanje}")]
    public async Task<IActionResult> PromeniStanje(int idKlijenta,string brRacuna, double novoStanje)
    {
        try
        {
            if(novoStanje < 0)
                return BadRequest("Novo stanje ne sme biti manje od 0!");

            Racun? r = await Context.Racuni
                                    .Where(p=> p.Klijent.ID == idKlijenta && p.BrojRacuna == brRacuna)
                                    .FirstOrDefaultAsync();
            if(r == null)
                return BadRequest("Ne postoji zadati racun proslednjenog klijenta!");


            double staroStanje = r.Sredstva;

            if(r.Sredstva > novoStanje)
                r.UkupanPodignutNovac += (r.Sredstva - novoStanje);
            r.Sredstva = novoStanje;

            Context.Racuni.Update(r);
            await Context.SaveChangesAsync();
            return Ok($"Stanje racuna [{r.BrojRacuna}] promenjeno: {staroStanje} -> {r.Sredstva}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("UkupanNovacBanke/{idBanke}")]
    public async Task<IActionResult> UkupanNovacBanke(int idBanke)
    {
        try
        {
            if((await Context.Banke.FindAsync(idBanke)) == null)
                return BadRequest("Ne postoji zadata banka!");
            var info = await Context.Racuni.Where(p => p.Banka.ID == idBanke)
                                            .ToListAsync();

            double suma = 0;
            foreach(var r in info)
                suma += (r.Sredstva + r.UkupanPodignutNovac);
            return Ok($"Ukupna suma novca u banci sa id {idBanke} = {suma}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }   
        
}
