using Microsoft.AspNetCore.Mvc;
using test3.Models;

namespace test3.Controllers;

[Route("[controller]")]

public class GradController : ControllerBase
{
    public WebContext webContext {get;set;}

    public GradController(WebContext wc)
    {
        webContext = wc;
    }

    [HttpGet("Vrati jedan")]
    public Grad VratiJedan()
    {
        return new Grad()
        {
            id=1,
            Ime="Krusevac",
            BrojStanovnika=250000
        };
    }

    [HttpGet("Vrati sve")]
    public List<Grad> VratiSve()
    {
        return webContext.Grad.ToList();
    }
}