
namespace Controllers;

[ApiController]
[Route("[controller]")]

public class GradController : ControllerBase
{
    public RestoraniContext restoraniContext {get;set;}
    public GradController(RestoraniContext rc)
    {
        restoraniContext = rc;
    }

    [HttpPost("DodajGrad")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> DodajGrad([FromBody] Grad grad)
    {
        try
        {
            if(String.IsNullOrEmpty(grad.Naziv))
            {
                return BadRequest("Naziv grada je neispravan!");
            }
            if(grad.BrojStanovnika < 1)
            {
                return BadRequest("Grad ne sme imati manje od jednog stanovnika!");
            }
            if(grad.Povrsina < 100)
            {
                return BadRequest("Minimalna prihvatljiva povrsina grada je 100!");
            }

            await restoraniContext.Gradovi.AddAsync(grad);
            await restoraniContext.SaveChangesAsync();
            return Ok($"Dodat je grad {grad.Naziv} sa Id: {grad.ID}!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    // [HttpPut("IzmeniGrad/{id}/{naziv}")]

    // public async Task<ActionResult> IzmeniGrad(int id, string naziv)
    // {
    //     try
    //     {
    //         //Prvi nacin
    //         //var grad = await restoraniContext.Gradovi.Where( x => x.ID == id).FirstOrDefaultAsync();

    //         //Drugi nacin radi samo sa ID
    //         var grad = await restoraniContext.Gradovi.FindAsync(id);

    //         if(grad == null)
    //         {
    //             return BadRequest($"Grad sa id: {id} nije pronadjen u bazi!");
    //         }

    //         grad.Naziv = naziv;

    //         restoraniContext.Gradovi.Update(grad);

    //         await restoraniContext.SaveChangesAsync();

    //         return Ok($"Grad sa id: {id} je uspesno zamenio naziv!");
    //     }
    //     catch(Exception e)
    //     {
    //         return BadRequest(e.Message);
    //     }

    // }

    [HttpPut("IzmeniGradFromBody")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> IzmeniGrad([FromBody] Grad grad)
    {
        try
        {
            //Prvi nacin
            //var grad = await restoraniContext.Gradovi.Where( x => x.ID == id).FirstOrDefaultAsync();

            //Drugi nacin radi samo sa ID
            //var grad = await restoraniContext.Gradovi.FindAsync(id);

            if(grad == null)
            {
                return BadRequest($"Grad nije pronadjen u bazi!");
            }

            restoraniContext.Gradovi.Update(grad);

            await restoraniContext.SaveChangesAsync();

            return Ok($"Uspesno izmenjeni podaci o gradu!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }

    }


    [HttpGet("PreuzmiGrad/{naziv}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> PreuzmiGrad(string naziv)
    {
        try
        {
            var grad = await restoraniContext.Gradovi.Where(x => x.Naziv == naziv).FirstOrDefaultAsync();
            return Ok(grad);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }

    }

    [HttpGet("PreuzmiGradCijaImenaPocinjuSa/{naziv}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> PreuzmiGradCijaImenaPocinjuSa(string naziv)
    {
        try
        {
            var gradovi = await restoraniContext.Gradovi.Where(x => x.Naziv.StartsWith("Ni")).FirstOrDefaultAsync();
            return Ok(gradovi);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }

    }

    [HttpDelete("ObrisiGrad")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> ObrisiGrad(int id)
    {
        try
        {
            var grad = await restoraniContext.Gradovi.FindAsync(id);
            
            if(grad == null)
                return BadRequest($"Grad sa id: {id} ne postoji u bazi!");

            restoraniContext.Gradovi.Remove(grad);

            restoraniContext.SaveChanges();
            
            return Ok("Uspesno obrisan grad sa id:" + id);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }

    }



    [HttpGet("PreuzmiGradXML/{naziv}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    [Produces("text/xml")] ///DA GA NAPRAVI KAO XML

    public async Task<ActionResult> PreuzmiGradXML(string naziv)
    {
        try
        {
            var grad = await restoraniContext.Gradovi.Where(x => x.Naziv == naziv).FirstOrDefaultAsync();
            return Ok(grad);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }

    }

    [HttpGet("GradoviInfo")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]

    public async Task<ActionResult> GradoviInfo()
    {
        try
        {
            var grad = await restoraniContext.Gradovi
            .Select(x => new
                {
                    x.Naziv,
                    x.ID,
                    x.BrojStanovnika
                }).ToListAsync();
            return Ok(grad);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }

    }

}