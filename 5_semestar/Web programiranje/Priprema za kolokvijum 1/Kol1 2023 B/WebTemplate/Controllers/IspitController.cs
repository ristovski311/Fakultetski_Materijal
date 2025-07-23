using System.Runtime.Intrinsics.Arm;

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

    [HttpPost("DodajStudenta")]
    public async Task<IActionResult> DodajStudenta([FromBody] Student s)
    {
        try
        {
            await Context.Studenti!.AddAsync(s);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat student {s.Ime} {s.Prezime}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

        [HttpPost("DodajFakultet")]
    public async Task<IActionResult> DodajFakultet([FromBody] Fakultet f)
    {
        try
        {
            await Context.Fakulteti!.AddAsync(f);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat student {f.Naziv}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

       [HttpPost("UpisiNaSmer/{idStudenta}/{idFakulteta}/{naziv}/{datumUpisa}/{esbp}")]
    public async Task<IActionResult> UpisiNaSmer(int idStudenta, int idFakulteta, string naziv, DateTime datumUpisa, int esbp)
    {
        try
        {
            Student? st = await Context.Studenti!.FindAsync(idStudenta);
            Fakultet? f = await Context.Fakulteti!.FindAsync(idFakulteta);

            if(st == null)
                return BadRequest("Nema takvog studenta!");

            if(f == null)
                return BadRequest("Nema takvog fakulteta!");

            Smer? vecPostoji = await Context.Smerovi!.Where(p => p.Student == st && p.Fakultet == f).FirstOrDefaultAsync();

            if(vecPostoji != null)
                return BadRequest("Vec je student upisan na taj fakultet!");

            Smer s = new Smer()
            {
                Student = st,
                Fakultet = f,
                Naziv = naziv,
                DatumUpisa = datumUpisa,
                ESPB = esbp
            };

            await Context.Smerovi!.AddAsync(s);
            await Context.SaveChangesAsync();
            return Ok($"Dodat student {st.Ime} {st.Prezime} na smer {s.Naziv} na fakultetu {f.Naziv}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }


    [HttpPut("PromeniStudenta")]
    public async Task<IActionResult> PromeniStudenta([FromBody] Student noviS)
    {
        try
        {
            Student? s = await Context.Studenti!.FindAsync(noviS.ID);
            if(s == null)
                return BadRequest("Ne mozete promeniti tog studenta jer ne postoji u bazi!");

            s.Ime = noviS.Ime;
            s.Prezime = noviS.Prezime;
            s.ZavrsenaSrednjaSkola = noviS.ZavrsenaSrednjaSkola;
            s.GodinaRodjenja = noviS.GodinaRodjenja;

            Context.Studenti.Update(s);
            await Context.SaveChangesAsync();
            return Ok($"Promenjene informacije za studenta sa indeksom: {s.Indeks}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("PronadjiStudente/{smer}/{datumOd}/{datumDo}")]
    public async Task<IActionResult> PronadjiStudente(string smer,DateTime datumOd, DateTime datumDo)
    {
        try
        {
            var studenti = await Context.Smerovi!.Include(p => p.Student)
                                                .Where(p => p.Naziv == smer)
                                                .Where(p => p.DatumUpisa < datumDo && p.DatumUpisa > datumOd)
                                                .Select(p => p.Student)
                                                .ToListAsync();     

            return Ok(studenti);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("ProsekESPB/{smer}")]
    public async Task<IActionResult> ProsekESPB(string smer)
    {
        try
        {
            var avg = Context.Smerovi!.Where(p => p.Naziv == smer)
                                                .Average(p => p.ESPB);  

            return Ok(avg);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

}
