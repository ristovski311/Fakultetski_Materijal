namespace restorani.Controllers;

[ApiController]
[Route("[controller]")]
public class GradController : ControllerBase
{
    public RestoraniContext restoraniContext { get; set; }

    public GradController(RestoraniContext context)
    {
        restoraniContext = context;
    }

    [HttpPost("DodajGrad")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> DodajGrad([FromBody] Grad grad)
    {
        try
        {
            if (string.IsNullOrWhiteSpace(grad.Naziv))
                return BadRequest("Naziv grada je neispravan");
            if (grad.BrojStanovnika <= 0)
                return BadRequest("Nemozete kreirati grad sa 0 stanovnika");
            if (grad.Povrsina <= 0)
                return BadRequest("Povrsina grada ne moze biti 0 m2");

            await restoraniContext.Gradovi.AddAsync(grad);
            await restoraniContext.SaveChangesAsync();
            return Ok($"Dodat je grad {grad.Naziv} sa Id-jem {grad.ID}");
            //Ok("Dodat je grad"+ grad.Naziv+" sa Id-jem"+ grad.ID);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }
    }

    [HttpPut("IzmeniGrad/{id}/{naziv}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> IzmeniGrad(int id, string naziv)
    {
        try
        {
            var grad = await restoraniContext.Gradovi.FindAsync(id);
            //await restoraniContext.Gradovi.Where(x=>x.ID==id).FirstOrDefaultAsync();
            if (grad == null)
                return BadRequest($"Grad sa ID:{id} nije pronadjen");
            grad.Naziv = naziv;
            restoraniContext.Gradovi.Update(grad);
            await restoraniContext.SaveChangesAsync();
            return Ok("Uspesno izmenjeno ime grada");
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }
    }

    [HttpPut("IzmeniGradFromBody")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> IzmeniGradFromBody([FromBody] Grad grad)
    {
        try
        {
            if (grad == null)
                return BadRequest("Grad nije pronadjen");

            restoraniContext.Gradovi.Update(grad);
            await restoraniContext.SaveChangesAsync();
            return Ok("Uspesno izmenjeni podaci o gradu");
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }
    }

    [HttpGet("PreuzmiGrad/{naziv}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> PreuzmiGrad(string naziv)
    {
        try
        {
            var grad = await restoraniContext.Gradovi
            .Where(x => x.Naziv == naziv)
            .FirstOrDefaultAsync();
            return Ok(grad);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }

    }

    [HttpGet("PreuzmiGradCijaImenaPocinjuSa/{naziv}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    public async Task<ActionResult> PreuzmiGradCijaImenaPocinjuSa(string naziv)
    {
        try
        {
            var gradovi = await restoraniContext.Gradovi
            .Where(x => x.Naziv.StartsWith(naziv))
            .ToListAsync();
            return Ok(gradovi);


        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
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
            if (grad == null)
                return BadRequest($"Grad sa Id:{id} ne postoji");

            restoraniContext.Gradovi.Remove(grad);
            await restoraniContext.SaveChangesAsync();
            return Ok("Uspesno obrisan grad");

        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }

    }

    [HttpGet("PreuzmiGradXML/{naziv}")]
    [ProducesResponseType(StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status400BadRequest)]
    [Produces("text/xml")]
    public async Task<ActionResult> PreuzmiGradXML(string naziv)
    {
        try
        {
            var grad = await restoraniContext.Gradovi.Where(x => x.Naziv == naziv)
            .FirstOrDefaultAsync();
            return Ok(grad);


        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
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
                Pera = x.Naziv,
                x.ID,
                x.BrojStanovnika
            })
            .ToListAsync();
            return Ok(grad);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }
    }

    //Na času nismo videli rezultate ove metode. Ona je zapravo radila, greškom sam skrolovala 
    // previše. Evo rezultata ispod, probajte
    //Za vraćanje rezultata u XML formatu dovoljno je dodati [Produces("text/xml")]
    //i dodati podršku u Program.cs --> AddXmlSerializerFormatters();

    //<Grad xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
    //<ID>1</ID>
    //<Naziv>Nis</Naziv>
    //<Povrsina>5000</Povrsina>
    //<BrojStanovnika>6000000</BrojStanovnika>
    //</Grad>


}