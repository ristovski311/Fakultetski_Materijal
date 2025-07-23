namespace restorani.Controllers;

[ApiController]
[Route("[controller]")]
public class RestoranController : ControllerBase
{
    public RestoraniContext restoraniContext;
    public RestoranController(RestoraniContext context)
    {
        restoraniContext = context;
    }

    [HttpGet("VratiRestoran/{id}")]
    public async Task<ActionResult> VratiRestoran(int id)
    {
        try
        {
            var r = await restoraniContext.Restorani.FindAsync(id);
            return Ok(r);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.InnerException);
        }
    }

    [HttpPost("DodajRestoran/{idGrad}/{tipHrane}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> DodajRestoran([FromBody] Restoran restoran,
     int idGrad, string tipHrane)
    {
        try
        {
            var grad = await restoraniContext.Gradovi.FindAsync(idGrad);
            if (grad == null)
                return BadRequest("Ne postoji grad");
            if (restoran.X <= 0 || restoran.Y < 0)
                return BadRequest("Morate uneti lokaciju restorana");
            if (string.IsNullOrWhiteSpace(restoran.Naziv))
                return BadRequest("Naziv restorana je obavezan podatak");

            restoran.Grad = grad;
            restoran.Tip = new TipRestorana { Naziv = tipHrane };

            await restoraniContext.Restorani.AddAsync(restoran);
            await restoraniContext.SaveChangesAsync();
            return Ok($"Uspesno dodat restoran ID:{restoran.ID}, sa nazivom {restoran.Naziv}");
        }
        catch (Exception ex)
        {
            return BadRequest(ex.InnerException);
        }
    }

    [HttpGet("PreuzmiRestoranGrada/{idGrad}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> PreuzmiRestoranGrada(int idGrad)
    {
        try
        {
            var restorani = await restoraniContext.Gradovi
              .Where(x => x.ID == idGrad)
                  .Include(x => x.Restorani)
                  .Select(x => new
                  {
                      x.Naziv,
                      x.Restorani
                  })
              .ToListAsync();
            //metoda iznad vraca grad sa svim njegovim restoranima
            //metoda ispod vraca grad i njegov jedan restoran - ZASTO?
            //var restorani1= await restoraniContext.Restorani
            //    .Include(x=>x.Grad)
            //    .Where(x=>x.ID==idGrad)
            //    .Select(x=> new
            //    {
            //        x.Grad!.Naziv,
            //        Restorani = x
            //    })
            //    .ToListAsync();
            return Ok(restorani);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.InnerException);
        }
    }

    [HttpGet("NajbliziRestoran/{x}/{y}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> NajbliziRestoran(double x, double y)
    {
        try
        {
            var r = await restoraniContext.Restorani
           .OrderBy(t =>
                 Math.Sqrt(Math.Pow(t.X - x, 2)
                     + Math.Pow(t.Y - y, 2)))
                 .FirstOrDefaultAsync();

            return Ok(r);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.InnerException);
        }
    }


    [HttpGet("PreuzmiRestoraneUBlizini/{x}/{y}/{udaljenost}/{tipHrane?}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> PreuzmiRestoraneUBlizini(double x, double y
    , int udaljenost, string? tipHrane = "")
    {
        try
        {
            var r = await restoraniContext.Restorani
            .Include(t => t.Tip)
            .Where(t =>
                 Math.Sqrt(Math.Pow(t.X - x, 2)
                 + Math.Pow(t.Y - y, 2)) < udaljenost)
             .Where(t =>
             !string.IsNullOrWhiteSpace(tipHrane)
             && t.Tip != null
             && t.Tip.Naziv == tipHrane
             || string.IsNullOrWhiteSpace(tipHrane))
             .Select(t => new
             {
                 t.ID,
                 t.Naziv,
                 t.X,
                 t.Y,
                 Ocena = t.UkupnaSumaOcena / (t.BrojOcenjivanja == 0 ? 1 : t.BrojOcenjivanja),
                 tipHrane = t.Tip!.Naziv

             })
             .ToListAsync();

            return Ok(r);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.InnerException);
        }
    }


    [HttpGet("VratiTipoveRestorana")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> VratiTipoveRestorana()
    {
        try
        {
            //tipovi samo onih restorana koji postoje
            // var tipovi = await restoraniContext.Restorani
            // .Include(x=>x.Tip)
            // .Where(x=>x.Tip!=null)
            // .Select(x=>x.Tip!.Naziv)
            // .Distinct()
            // .ToListAsync();
            // return Ok(tipovi);

            //svi tipovi restorana iz baze, bez obzira da li postoji
            //tavak restoran ili ne
            var tipoviSvi = await restoraniContext.TipRestorana
            .Select(x => x.Naziv)
            .Distinct()
            .ToListAsync();
            return Ok(tipoviSvi);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.InnerException);
        }
    }



    [HttpGet("VratiRestoraneTipova")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> VratiRestoraneTipova([FromQuery] string[] tip) //Obratite paznju, prosledjuje se lista tipova
    {
        try
        {
            var restorani = await restoraniContext.Restorani
            .Include(x => x.Tip)
            .Include(x => x.Grad)
            .Where(x => x.Tip != null && tip.Contains(x.Tip.Naziv))
            .ToListAsync();

            return Ok(restorani);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.InnerException);
        }
    }

    [HttpGet("VratiMeniRestorana/{idRestorana}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> VratiMeniRestorana(int idRestorana)
    {
        try
        {
            var meni = await restoraniContext.Jela
            .Include(x => x.Restoran)
            .Where(x => x.Restoran != null && x.Restoran.ID == idRestorana)
            .ToListAsync();

            return Ok(new
            {
                MeniJela = meni.Where(x => x.DaLiJeJelo).ToList(),
                MeniPica = meni.Where(x => !x.DaLiJeJelo).ToList()
            });
        }
        catch (Exception ex)
        {
            return BadRequest(ex.InnerException);
        }
    }


    //nismo radili na casu, pogledajte
    [HttpPost("OcenjivanjeRestorana/{idRestorana}/{ocena}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> OcenjivanjeRestorana(int idRestorana, int ocena)
    {
        try
        {
            if (ocena > 10 || ocena < 0)
            {
                return BadRequest("Vrednost ocene mora da bude između 0 i 10.");
            }

            var restoran = await restoraniContext.Restorani.FindAsync(idRestorana);

            if (restoran == null)
            {
                return BadRequest("Restoran sa zadatim ID-jem nije pronađen.");
            }

            restoran.UkupnaSumaOcena += ocena;
            restoran.BrojOcenjivanja++;

            await restoraniContext.SaveChangesAsync();

            return Ok("Ocena uspesno upisana.");
        }
        catch (Exception e)
        {
            return BadRequest(e.InnerException);
        }
    }
}