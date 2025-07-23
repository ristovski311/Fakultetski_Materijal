using Microsoft.AspNetCore.Mvc;
using test2.Models;

namespace test2.Controllers;

[Route("[controller]")]
public class GradController : ControllerBase
{
    public WebContext webContext {get;set;}

    public GradController(WebContext wc)
    {
        webContext = wc;
    }

    [HttpGet("Jedan")]
    public Grad vratiJedanGrad()
    {
        return new Grad()
        {
            id = 1,
            Naziv = "Beoooooograd",
            Opstina = "Beooooogradska",
            BrojStanovnika = 19
        };
    }

    [HttpGet("Sve")]

    public List<Grad> vratiSveGradove()
    {
        return webContext.Grad.ToList();
    }
}