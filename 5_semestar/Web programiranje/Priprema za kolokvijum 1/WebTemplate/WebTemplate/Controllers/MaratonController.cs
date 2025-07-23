namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]

public class MaratonController : ControllerBase
{    private MaratonContext context; 
    public MaratonController(MaratonContext c)
    {
        context = c;
    }

    [HttpPost("DodavanjeSportiste")]
    public async Task<IActionResult> DodavanjeSportiste([FromBody] Sportista sportista)
    {
        try
        {
            await context.Sportisti.AddAsync(sportista);
            await context.SaveChangesAsync();
            return Ok($"Uspesno dodat sportista sa ID: {sportista.ID}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }
    
    [HttpPost("DodavanjeDiscipline/{naziv}/{opis}/{brojTakmicara}/{datumOdKadaPostoji}")]
    public async Task<IActionResult> DodavanjeDiscipline(string naziv, string opis, int brojTakmicara, DateTime datumOdKadaPostoji)
    {
        try
        {
            var disciplina = new Disciplina()
            {
                Naziv = naziv,
                Opis = opis,
                BrojTakmicara = brojTakmicara,
                DatumOdKadaPostoji = datumOdKadaPostoji
            };

            await context.Discipline.AddAsync(disciplina);
            await context.SaveChangesAsync();

            return Ok($"Dodata disciplina sa id: {disciplina.ID}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpDelete("BrisanjeRekorda/{idRekorda}")]
    public async Task<IActionResult> BrisanjeRekorda(int idRekorda)
    {
        try
        {
            var rekord = await context.Rekordi.FindAsync(idRekorda);
            string takmicenje;

            if(rekord != null)
                {
                    takmicenje = rekord.Takmicenje;
                    context.Rekordi.Remove(rekord);
                    await context.SaveChangesAsync();
                }
            else
                return BadRequest($"Rekord sa id: {idRekorda} nije pronadjen!");
            return Ok($"Uspesno obrisan rekord sa takmicenja {takmicenje} sa id: {idRekorda}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("PronalazenjeRekordera/{datum}")]
    public async Task<IActionResult> PronalazenjeRekordera(DateTime datum)
    {
        try
        {
            var sportisti = await context.Rekordi
                                            .Include(p => p.Sportista)
                                            .ThenInclude(p => p!.Sportovi)
                                            .Where(p => p.OstvarenDana >= datum)
                                            .Select(p => p.Sportista)
                                            .ToListAsync();

            return Ok(sportisti);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }
 
    [HttpGet("PronadjiDisciplinu")]
    public async Task<IActionResult> PronadjiDisciplinu()
    {
        try
        {
            var disciplina = await context.Discipline.Where(p => p.Rekordi!.Count < 10)
                                                    .OrderByDescending(p => p.DatumOdKadaPostoji)
                                                    .FirstOrDefaultAsync();
            if(disciplina == null)
                return Ok("Nema");
            return Ok(disciplina);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

[HttpPost("DodajRekord")]
    public async Task<IActionResult> DodajRekord([FromBody] RekordZaSlanje rekordZaSlanje)
    {
        try
        {
            var sportista = await context.Sportisti.FindAsync(rekordZaSlanje.SportistaID);
            var disciplina = await context.Discipline.FindAsync(rekordZaSlanje.DisciplinaID);

            var Rekord = new Rekord()
            {
                Takmicenje = rekordZaSlanje.Takmicenje,
                OstvarenDana = rekordZaSlanje.Datum,
                Sportista = sportista,
                Disciplina = disciplina
            };

            await context.Rekordi.AddAsync(Rekord);
            await context.SaveChangesAsync();

            return Ok("Dodat novi rekord!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

}