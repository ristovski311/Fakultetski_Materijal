namespace restorani.Controllers;

[ApiController]
[Route("[controller]")]
public class SastojakController : ControllerBase
{
    public RestoraniContext restoraniContext;
    
    public SastojakController(RestoraniContext context)
    {
        restoraniContext = context;
    }

    [HttpPost]
    [Route("DodavanjeSastojka")]
    public async Task<ActionResult> DodavanjeSastojka(
        [FromBody] Sastojak sastojak)
    {
        try
        {
            await restoraniContext.Sastojci.AddAsync(sastojak);
            await restoraniContext.SaveChangesAsync();
            return Ok($"Sastojak: {sastojak.Naziv} je dodat.");
        }
        catch (Exception e)
        {
            return BadRequest(e.ToExceptionString());
        }
    }

    [HttpPost]
    [Route("DodavanjeSastojkaMagacinuRestorana/{idRestorana}/{idSastojka}/{kolicina}")]
    public async Task<ActionResult> DodavanjeSastojkaMagacinuRestorana(int idRestorana,
                                                                       int idSastojka,
                                                                       int kolicina)
    {
        try
        {
            var restoran = await restoraniContext.Restorani.FindAsync(idRestorana);
            var sastojak = await restoraniContext.Sastojci.FindAsync(idSastojka);

            if (restoran == null || sastojak == null)
            {
                return BadRequest($"Podaci nisu validni.");
            }

            Magacin m = new()
            {
                Kolicina = kolicina,
                Restoran = restoran,
                Sastojak = sastojak
            };

            await restoraniContext.MagaciniRestorana.AddAsync(m);
            await restoraniContext.SaveChangesAsync();

            return Ok($"Upisan je sastojak u magacin restorana.");
        }
        catch (Exception e)
        {
            return BadRequest(e.ToExceptionString());
        }
    }
}
