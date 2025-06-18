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

    [HttpPost("DodajAerodrom")]
    public async Task<IActionResult> DodajAerodrom([FromBody] Aerodrom a)
    {
        try
        {
            await Context.Aerodromi.AddAsync(a);
            await Context.SaveChangesAsync();
            return Ok($"Dodat novi aerodrom: {a.Naziv}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodajLetelicu/{naziv}/{kapacitetPutnika}/{brojOsoblja}/{brojMotora}")]
    public async Task<IActionResult> DodajLetelicu(string naziv, int kapacitetPutnika, int brojOsoblja, int brojMotora)
    {
        try
        {
            Letelica l = new Letelica()
            {
                Naziv = naziv,
                KapacitetPutnika = kapacitetPutnika,
                BrojOsoblja = brojOsoblja,
                BrojMotora = brojMotora
            };
            await Context.Letelice.AddAsync(l);
            await Context.SaveChangesAsync();
            return Ok($"Dodata letelica s nazivom: {l.Naziv}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodajLet/{idAerodromaPolaska}/{idAerodromaDolaska}/{idLetelice}/{brojPutnika}/{vremePolaska}/{vremeDolaska}")]
    public async Task<IActionResult> DodajLet(int idAerodromaPolaska,
                                                int idAerodromaDolaska,
                                                int idLetelice,
                                                int brojPutnika,
                                                DateTime vremePolaska,
                                                DateTime vremeDolaska)
    {
        try
        {

            Aerodrom? aP = await Context.Aerodromi.FindAsync(idAerodromaPolaska);
            Aerodrom? aD = await Context.Aerodromi.FindAsync(idAerodromaDolaska);

            if(aD == null || aP == null)
                return BadRequest("Ne postoje specificirani aerodromi!");

            Letelica? l = await Context.Letelice.FindAsync(idLetelice);

            if(l == null) 
                return BadRequest("Ne postoji prosledjena letelica!");

            if(l.KapacitetPutnika < brojPutnika) 
                return BadRequest("Previse putnika za ovu letelicu!");


            Relacija? r = await Context.Relacije.FirstOrDefaultAsync(p => p.AerodromOd!.ID == idAerodromaPolaska
                                                            && p.AerodromDo!.ID == idAerodromaDolaska);
            if(r == null)
            {
                r = new Relacija()
                {
                    AerodromOd = aP,
                    AerodromDo = aD
                };
                await Context.Relacije.AddAsync(r);
                await Context.SaveChangesAsync();
            }

            Let noviLet = new Let()
            {
                Letelica = l,
                Relacija = r,
                BrojPutnika = brojPutnika,
                VremePoletanja = vremePolaska,
                VremeSletanja = vremeDolaska
            };

            await Context.Letovi.AddAsync(noviLet);

            await Context.SaveChangesAsync();
            return Ok($"Dodat novi let sa relacijom: {aP.Naziv}, {aP.Lokacija} -> {aD.Naziv}, {aD.Lokacija}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("PronadjiLet/{idAerodromaPolaska}")]
    public async Task<IActionResult> PronadjiLet(int idAerodromaPolaska)
    {
        try
        {
            List<Let>? letovi = await Context.Letovi.Include(p=>p.Relacija)
                                                    .ThenInclude(p=>p.AerodromOd)
                                                    .Include(p=>p.Relacija)
                                                    .ThenInclude(p=>p.AerodromDo)
                                                    .Include(p=>p.Letelica)
                                                    .Where(p => p.Relacija.AerodromOd!.ID == idAerodromaPolaska)
                                                    .ToListAsync();
                                                    
            if(letovi == null)
                return BadRequest("Null je letovi");
            if(letovi.Count == 0)
                return BadRequest("Nema ni 1");

            return Ok(letovi);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("ProsecnaDuzinaLeta/{idAerodroma1}/{idAerodroma2}")]
    public async Task<IActionResult> ProsecnaDuzinaLeta(int idAerodroma1,int idAerodroma2)
    {
        try
        {
            List<Let>? letovi = await Context.Letovi.Include(p=>p.Relacija)
                                                    .ThenInclude(p=>p.AerodromOd)
                                                    .Include(p=>p.Relacija)
                                                    .ThenInclude(p=>p.AerodromDo)
                                                    .Where(p => (p.Relacija.AerodromOd!.ID == idAerodroma1 && p.Relacija.AerodromDo!.ID == idAerodroma2)
                                                                || (p.Relacija.AerodromOd!.ID == idAerodroma2 && p.Relacija.AerodromDo!.ID == idAerodroma1))
                                                    .ToListAsync();
                                 
            TimeSpan sum = new TimeSpan(0,0,0);

            foreach(var l in letovi)
            {
                sum += (l.VremeSletanja - l.VremePoletanja);
            }

            sum.Divide(letovi.Count);


            return Ok($"Prosecna duzina leta izmedju {idAerodroma1} i {idAerodroma2} je {sum}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }



    
}
