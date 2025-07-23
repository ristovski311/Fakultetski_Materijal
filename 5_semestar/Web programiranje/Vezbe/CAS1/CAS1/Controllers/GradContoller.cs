using CAS1.Models;
using Microsoft.AspNetCore.Mvc;

namespace CAS1.Controllers;

[Route("[controller]")]
public class GradContoller:ControllerBase
{

    public WebContext webContext {get; set;}
    public GradContoller(WebContext context)
    {
        webContext=context;
    }

    [HttpGet("VratiNis")]
    public Grad VratiNis()
    {
        return new Grad()
        {
            id=1,
            Naziv="Nis",
            BrojStanovnika=300000
        };
    }
    [HttpGet("VratiSveGradove")]
    public List<Grad> VratiGradove()
    {
        return webContext.Grad.ToList();
    }
}