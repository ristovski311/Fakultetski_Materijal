using System.Runtime.Intrinsics.Arm;

namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class IspitController : ControllerBase
{
    public IspitContext Context { get; set; }

    public IspitController(IspitContext context)
    {
        Context = context;
    }

    [HttpPost("DodavanjeED")]
    public async Task<IActionResult> DodavanjeED([FromBody] Elektrodistribucija ed)
    {
        try
        {
            await Context.Elektrodistribucije!.AddAsync(ed);
            await Context.SaveChangesAsync();
            return Ok($"Dodata elektrodistribucija: {ed.Naziv}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodavanjePotrosaca/{ime}/{prezime}/{godinaRodjenja}/{mestoRodjenja}")]
    public async Task<IActionResult> DodavanjePotrosaca(string ime, string prezime, int godinaRodjenja, string mestoRodjenja)
    {
        try
        {
            Potrosac p = new Potrosac()
            {
                Ime = ime,
                Prezime = prezime,
                GodinaRodjenja = godinaRodjenja,
                MestoRodjenja = mestoRodjenja
            };

            await Context.Potrosaci!.AddAsync(p);
            await Context.SaveChangesAsync();
            return Ok($"Registrovan potrosac: {p.Ime} {p.Prezime}");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodavanjeDPPotrosacu/{idPotrosaca}/{idDP}/{korisnickiBroj}/{vremePotpisivanjaUgovora}/{brojBrojila}")]
    public async Task<IActionResult> DodavanjeDPPotrosacu(int idPotrosaca,int idDP, int korisnickiBroj, DateTime vremePotpisivanjaUgovora, int brojBrojila)
    {
        try
        {
           DP? dp = await Context.DPovi!.FindAsync(idDP);
           Potrosac? p = await Context.Potrosaci!.FindAsync(idPotrosaca);

            if(p == null)
                return BadRequest("Ne postoji potrosac sa datim id-jem!");

            if(dp == null)
            {
                DP newDp = new DP
                {
                    Naziv = new string("DP" + idDP)
                };
                dp = newDp;
                await Context.DPovi!.AddAsync(newDp);
                await Context.SaveChangesAsync();
            }

            DPPotrosac newdpP = new DPPotrosac()
            {
                Potrosac = p,
                DP = dp,
                KorisnickiBroj = korisnickiBroj,
                DatumPotpisivanjaUgovora = vremePotpisivanjaUgovora,
                BrojBrojila = brojBrojila
            };

            await Context.Ugovori!.AddAsync(newdpP);
            await Context.SaveChangesAsync();
            return Ok($"Dodati novi podaci o potrosacu: {p.Ime} {p.Prezime} u DP {dp.Naziv}, sa {newdpP.BrojBrojila} brojila!");
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("PronadjiPotrosace/{brojBrojila}")]
    public async Task<IActionResult> PronadjiPotrosace(int brojBrojila)
    {
        try
        {
            List<DPPotrosac> dppotr = await Context.Ugovori!.Include(p => p.Potrosac)
                                                            .Where(p => p.BrojBrojila == brojBrojila)
                                                            .ToListAsync();

            List<Potrosac> potrosaci = [];

            foreach(var d in dppotr)
            {
                potrosaci.Add(d.Potrosac);
            }

            return Ok(potrosaci);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }
    
     [HttpGet("PronadjiPotrosaceUgovor/{datumOd}/{datumDo}")]
    public async Task<IActionResult> PronadjiPotrosaceUgovor(DateTime datumOd, DateTime datumDo)
    {
        try
        {
            List<Potrosac> potrosaci = await Context.Ugovori!.Include(p=>p.Potrosac)
                                                            .Where(p => p.DatumPotpisivanjaUgovora < datumDo && p.DatumPotpisivanjaUgovora > datumOd)
                                                            .GroupBy(p => p.Potrosac)
                                                            .Where(p=>p.Select(p=>p.DP).Distinct().Count() == 1)
                                                            .Select(p => p.Key)
                                                            .ToListAsync();
            return Ok(potrosaci);
        }
        catch(Exception e)
        {
            return BadRequest(e.Message);
        }
    }
}
