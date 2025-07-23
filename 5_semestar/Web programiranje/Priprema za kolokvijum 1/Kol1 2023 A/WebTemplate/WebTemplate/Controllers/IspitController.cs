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

    [HttpPost("DodavanjeAutora")]
    public async Task<IActionResult> DodavanjeAutora([FromBody] Autor a)
    {
        try
        {

            await Context.Autori.AddAsync(a);
            await Context.SaveChangesAsync();
            return Ok($"Dodat je autor: {a.Ime} {a.Prezime}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }
    [HttpPost("DodavanjeIzdavackeKuce")]
    public async Task<IActionResult> DodavanjeIzdavackeKuce([FromBody] IzdavackaKuca i)
    {
        try
        {

            await Context.IzdavackeKuce.AddAsync(i);
            await Context.SaveChangesAsync();
            return Ok($"Dodata je izdavacka kuda: {i.Naziv}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    // [HttpPost("DodavanjeKnjige/{idAutora}/{idIzdavackeKuce}/{naslov}/{datumObjavljivanja}/{brojStranica}/{zanr}/{isbn}")]
    // public async Task<IActionResult> DodavanjeKnjige(int idAutora,
    //                                                 int idIzdavackeKuce,
    //                                                 string naslov,
    //                                                 DateTime datumObjavljivanja,
    //                                                 int brojStranica,
    //                                                 string zanr,
    //                                                 string isbn)
    // {
    //     try
    //     {

    //         Autor? a = await Context.Autori.FindAsync(idAutora);
    //         if(a == null)
    //             return BadRequest("Ne postoji dati autor u bazi!");

    //         IzdavackaKuca? ik = await Context.IzdavackeKuce.FindAsync(idIzdavackeKuce);
    //         if(a == null)
    //             return BadRequest("Ne postoji data izdavacka kuca u bazi!");

    //         Knjiga k = new Knjiga()
    //         {
    //             Autor = a,
    //             Naslov = naslov,
    //             BrojStranica = brojStranica,
    //             ISBN = isbn,
    //             DatumObjavljivanja = datumObjavljivanja,
    //             Zanr = zanr
    //         };

    //         Ugovor u = new Ugovor()
    //         {
    //             Autor= a,
    //             IzdavackaKuca = ik,
    //             Knjiga = k,
    //             DatumPotpisa = DateTime.Now
    //         };

    //         await Context.Knjige.AddAsync(k);
    //         await Context.Ugovori.AddAsync(u);

    //         await Context.SaveChangesAsync();
    //         return Ok($"Dodata nova knjiga: {k.Naslov} ({a.Ime} {a.Prezime}) / ({ik!.Naziv})");
    //     }
    //     catch(Exception e)
    //     {
    //         return BadRequest(e.Message);
    //     }
    // }

    [HttpPost("DodavanjeKnjige")]
    public async Task<IActionResult> DodavanjeKnjige([FromBody] Knjiga k, [FromQuery] int idAutora, [FromQuery] int idIzdavackeKuce)
    {
        try
        {

            Autor? a = await Context.Autori.FindAsync(idAutora);
            if(a == null)
                return BadRequest("Ne postoji dati autor u bazi!");

            IzdavackaKuca? ik = await Context.IzdavackeKuce.FindAsync(idIzdavackeKuce);
            if(a == null)
                return BadRequest("Ne postoji data izdavacka kuca u bazi!");

            k.Autor = a;

            Ugovor u = new Ugovor()
            {
                Autor= a,
                IzdavackaKuca = ik,
                Knjiga = k,
                DatumPotpisa = DateTime.Now
            };

            await Context.Knjige.AddAsync(k);
            await Context.Ugovori.AddAsync(u);

            await Context.SaveChangesAsync();
            return Ok($"Dodata nova knjiga: {k.Naslov} ({a.Ime} {a.Prezime}) / ({ik!.Naziv})");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }


    [HttpPut("IzmenaKnjige")]
    public async Task<IActionResult> IzmenaKnjige([FromBody] Knjiga k)
    {
        try
        {
            Knjiga? staraKnjiga = await Context.Knjige.FindAsync(k.ID);
            if(staraKnjiga == null)
                return BadRequest("Ne mozete promeniti knjigu koja ne postoji u bazi!");
            staraKnjiga.ISBN = k.ISBN;
            staraKnjiga.Naslov = k.Naslov;
            staraKnjiga.Zanr = k.Zanr;
            staraKnjiga.BrojStranica = k.BrojStranica;
            Context.Knjige.Update(staraKnjiga);
            await Context.SaveChangesAsync();
            return Ok($"Izmenjena knjiga: {k.Naslov}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpDelete("BrisanjeKnjige/{idKnjige}")]
    public async Task<IActionResult> BrisanjeKnjige(int idKnjige)
    {
        try
        {
            Knjiga? k = await Context.Knjige.FindAsync(idKnjige);
            
            if(k == null)
                return BadRequest("Ne postoji takva knjiga!");

            string naslov = k.Naslov;

            Ugovor? u = await Context.Ugovori.Where(u => u.Knjiga!.ID == k.ID).FirstOrDefaultAsync();

            Context.Ugovori.Remove(u!);

            Context.Knjige.Remove(k);
            
            await Context.SaveChangesAsync();
            return Ok($"Izbacena je knjiga : {naslov}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message + e.InnerException!.Message);
        }
    }

    [HttpGet("InfoOKnjigama/{datumOd}/{datumDo}")]
    public async Task<IActionResult> InfoOOknjigama(DateTime datumOd, DateTime datumDo)
    {
        try
        {
            var info = await Context.Ugovori.Include(u => u.Knjiga)
                                            .Where(u => u.DatumPotpisa < datumDo && u.DatumPotpisa > datumOd)
                                            .Select(u => u.Knjiga)
                                            .ToListAsync();
            return Ok(info);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("Period/{nazivIzdavackeKuce}")]
    public async Task<IActionResult> Period(string nazivIzdavackeKuce)
    {
        try
        {
            var info = await Context.Ugovori.Include(p => p.IzdavackaKuca)
                                            .Where(p=> p.IzdavackaKuca!.Naziv == nazivIzdavackeKuce)
                                            .OrderBy(p => p.DatumPotpisa)
                                            .ToListAsync();
            
            if(info == null || info.Count == 0)
                return Ok("Nema ugovora s tom izdavackom kucom!");

            DateTime periodOd = info[0].DatumPotpisa;
            DateTime periodDo = info[info.Count - 1].DatumPotpisa;

            return Ok($"Period prve do poslednje knjige za izdavacku kucu {nazivIzdavackeKuce}: {periodOd} -> {periodDo}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }
        
}
