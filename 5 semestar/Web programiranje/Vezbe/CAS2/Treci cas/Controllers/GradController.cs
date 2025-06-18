namespace DrugiCas.Controllers;

[ApiController]
[Route("[controller]")]
public class GradController : ControllerBase
{
    public RestoraniContext Context { get; set; }

    public GradController(RestoraniContext c)
    {
        Context = c;
    }

    [HttpGet("Preuzmi")]
    public async Task<IActionResult> Preuzmi()
    {
        // Nikada ne vraćajte celu tabelu iz baze podataka u memoriju!
        var gradovi = await Context.Gradovi.ToListAsync();
        return Ok(gradovi);
    }
}