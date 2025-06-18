using System.Security.Principal;

namespace restorani.Controllers;

[ApiController]
[Route("[controller]")]
public class MeniController : ControllerBase
{
    public RestoraniContext restoraniContext;

    public MeniController(RestoraniContext context)
    {
        restoraniContext = context;
    }

    [HttpPost]
    [Route("DodavanjeJela/{restoranID}")]
    public async Task<ActionResult> DodavanjeJela(
        [FromBody] JelaSaSastojcima jelaSaSastojcima,
        [FromRoute] int restoranID)
    {
        try
        {
            var restoran = await restoraniContext.Restorani.FindAsync(restoranID);

            if (restoran == null)
            {
                return BadRequest($"Restoran ne postoji.");
            }

            Jelo jelo = jelaSaSastojcima.Jelo;
            jelo.Restoran = restoran;
            jelo.Sastojci = [];

            foreach (var ssk in jelaSaSastojcima.Sastojci)
            {
                var sastojak = await restoraniContext.Sastojci.FindAsync(ssk.IdSastojka);

                if (sastojak == null)
                {
                    return BadRequest("Sastojak nije pronađen.");
                }

                var js = new JeloSastojak()
                {
                    Jelo = jelo,
                    Sastojak = sastojak,
                    Kolicina = ssk.Kolicina
                };

                jelo.Sastojci.Add(js);
            }

            await restoraniContext.Jela.AddAsync(jelo);
            await restoraniContext.SaveChangesAsync();

            return Ok("Uspesno upisano jelo.");
        }
        catch (Exception e)
        {
            return BadRequest(e.ToExceptionString());
        }
    }

    [HttpDelete]
    [Route("ObrisatiJelo/{idJela}")]
    public async Task<ActionResult> ObrisatiJelo(int idJela)
    {
        try
        {
            var jelo = await restoraniContext.Jela.FindAsync(idJela);

            if (jelo == null)
            {
                return BadRequest("Jelo nije pronadjeno.");
            }

            restoraniContext.Jela.Remove(jelo);
            await restoraniContext.SaveChangesAsync();
            return Ok("Uspesno obrisano jelo.");
        }
        catch (Exception e)
        {
            return BadRequest(e.ToExceptionString());
        }
    }

    [HttpGet]
    [Route("NarucivanjeJela/{idJela}")]
    public async Task<ActionResult> NarucivanjeJela(int idJela)
    {
        try
        {
            var jelo = await restoraniContext
            .Jela
            .Include(p => p.Restoran)
            .ThenInclude(p => p!.Magacin)
            .Include(p => p.Sastojci!)
            .ThenInclude(p => p.Sastojak)
            .Where(p => p.ID == idJela)
            .FirstOrDefaultAsync();

            if (jelo == null)
            {
                return BadRequest("Žao nam je, jelo nije na meniju.");
            }

            if (!await Kuhinja.ProveriDaLiMozeDaSePripremi(restoraniContext, jelo))
            {
                return BadRequest($"Jelo ne može da bude pripremljeno. Izvinite.");
            }

            if (await Kuhinja.PripremiJelo(restoraniContext, jelo, 4, 400))
            {
                return Ok($"Jelo će uskoro biti spremno. Prijatno!");
            }

            return BadRequest($"Imamo problema u kuhinji, žao nam je.");
        }
        catch (Exception e)
        {
            return BadRequest(e.ToExceptionString());
        }
    }
}
