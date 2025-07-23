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
            try{
                    var restoran = await restoraniContext.FindAsync(id);
                    return Ok("GRadi");
            }
            catch(Exception e)
            {
                return BadRequest(e.Message);
            }
    }
}