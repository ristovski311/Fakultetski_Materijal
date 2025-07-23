namespace Controllers;

[ApiController]
[Route("[controller]")]

public class RestoranController : ControllerBase
{
    public RestoraniContext restoraniContext {get;set;}
    public RestoranController(RestoraniContext rc)
    {
        restoraniContext = rc;
    }

    [HttpGet("VratiRestoran/{id}")]

    public async Task<ActionResult> VratiRestoran(int id)
    {
        try
        {
            var r = await restoraniContext.Restorani.FindAsync(id);
            return Ok(r);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodajRestoran/{idGrada}/{tipHrane}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> DodajRestoran([FromBody] Restoran restoran,int idGrada, string tipHrane)
    {
        try
        {
            var grad = await restoraniContext.Gradovi.FindAsync(idGrada);
            if(grad == null)
            {
                return BadRequest("Ne postoji grad!");
            }
            if(restoran.X <= 0 || restoran.Y <= 0)
            {
                return BadRequest("Morate uneti lokaciju restorana!");
            }
            if(string.IsNullOrWhiteSpace(restoran.Naziv) == true)
            {
                return BadRequest("Nazivan restorana je obavezan podatak!");   
            }
            restoran.Grad = grad;
            restoran.Tip = new Models.TipRestorana{Naziv = tipHrane};
            await restoraniContext.Restorani.AddAsync(restoran);
            await restoraniContext.SaveChangesAsync();
            return Ok($"Uspesno dodat restoran ID: {restoran.ID}, sa nazivom: {restoran.Naziv}");

        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }


    [HttpGet("PreuzmiRestoraneGrada/{idGrada}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> PreuzmiRestoraneGrada(int idGrada)
    {
        try
        {
            //Prvi nacin

            // var restorani = await restoraniContext.Restorani
            // .Include(x=>x.Grad)
            // .Where(x => x.ID == idGrada)
            // .ToListAsync();
            // return Ok(restorani);

            // INCLUDE:::::

            // var retsotrani = await restoraniContext.Gradovi
            // .Where(x => x.ID == idGrada)
            // .Include(x => x.Restorani)
            // .ThenInclude(x => x.Meni)
            // .ThenInclude(x => x.Sastojci)
            // .Include(x => x.Restorani)
            // .ThenInclude(x => x.Magacin)
            // .ToListAsync();


            
            var restorani = await restoraniContext.Gradovi
            .Where(x => x.ID == idGrada)
            .Include(x => x.Restorani)
            .Select(x => new
            {
                x.Naziv,
                x.Restorani
            })
            .ToListAsync();
            return Ok(restorani);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
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
            .OrderBy(t=> Math.Sqrt(Math.Pow(t.X - x, 2) + Math.Pow(t.Y - y, 2)))
            .FirstOrDefaultAsync();

            return Ok(r);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("PreuzmiRestoraneUBlizini/{x}/{y}/{udaljenost}/{tipHrane}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> PreuzmiRestoraneUBlizini(double x, double y, int udaljenost, string? tipHrane)
    {
        try
        {   
            var r = await restoraniContext.Restorani
            .Include(x => x.Tip)
            .Where(t=> Math.Sqrt(Math.Pow(t.X - x, 2) + Math.Pow(t.Y - y, 2)) < udaljenost)
            .Where(t => !string.IsNullOrEmpty(tipHrane) && t.Tip != null && t.Tip.Naziv == tipHrane)
            .Select(t => new {
                t.ID,
                t.Naziv,
                t.X,
                t.Y,
                Ocena = t.UkupnaSumaOcena / (t.BrojOcenjivanja == 0 ? 1 : t.BrojOcenjivanja),
                tipHrane = t.Tip!.Naziv
            }).ToListAsync();

            return Ok(r);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }



    [HttpGet("VratiTipoveRestorane")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> VratiTipoveRestorane()
    {
        try
        {   
            //TIPOVI SAMO ONIH RESTORANA KOJI POSTOJE!

            var tipovi = await restoraniContext.Restorani
            .Include(x => x.Tip)
            .Where(x=> x.Tip!= null)
            .Select(x => x.Tip!.Naziv)
            .Distinct()
            .ToListAsync();

            //SVI TIPOVI

            // var tipovi = await restoraniContext.TipRestorana
            // .Select(x => x.Naziv)
            // .Distinct()
            // .ToListAsync();

            return Ok(tipovi);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("VratiRestoraneTipova")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> VratiRestoraneTipova([FromQuery] string[] tip)
    {
        try
        {   
            var restorani = await restoraniContext.Restorani
            .Include(c => c.Tip)
            .Include(x => x.Grad)
            .Where(x=> x.Tip!= null && tip.Contains(x.Tip.Naziv))
            .ToListAsync();

            return Ok(restorani);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
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
            .Where(x=>x.Restoran != null && x.Restoran.ID == idRestorana)
            .ToListAsync();

            return Ok(new {
                MeniJela = meni.Where(x => x.DaLiJeJelo == true).ToList(),
                MeniPica = meni.Where(x => x.DaLiJeJelo == false).ToList()
            });
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }



}