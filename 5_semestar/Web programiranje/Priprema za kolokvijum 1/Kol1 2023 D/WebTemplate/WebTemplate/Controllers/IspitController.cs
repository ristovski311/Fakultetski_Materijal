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

    [HttpPost("DodavanjeProizvoda")]
    public async Task<IActionResult> DodavanjeProizvoda([FromBody] Proizvod p)
    {
        try
        {
            await Context.Proizvodi.AddAsync(p);
            await Context.SaveChangesAsync();
            return Ok(p);
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodavanjeProdavnice")]
    public async Task<IActionResult> DodavanjeProdavnice([FromBody] Prodavnica p)
    {
        try
        {
            await Context.Prodavnice.AddAsync(p);
            await Context.SaveChangesAsync();
            return Ok($"Uspesno dodat prodavnica {p.Naziv}!");
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("DodavanjeArtikla/{idProizvoda}/{idProdavnice}/{cena}")]
    public async Task<IActionResult> DodavanjeArtikla(int idProdavnice, int idProizvoda, int cena)
    {
        try
        {
            Prodavnica? p = await Context.Prodavnice.FindAsync(idProdavnice);
            Proizvod? pr = await Context.Proizvodi.FindAsync(idProizvoda);

            if (p == null)
                return BadRequest("Ne postoji prodavnica!");
            if (pr == null)
                return BadRequest("Ne postoji proizvod!");

            Artikal a = new Artikal()
            {
                Proizvod = pr,
                Prodavnica = p,
                Cena = cena,
                Kolicina = 10
            };

            await Context.Artikli.AddAsync(a);
            await Context.SaveChangesAsync();

            return Ok(new
            {
                pr.ID,
                pr.Naziv,
                pr.RokTrajanja,
                cena
            });
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPut("IzmenaProizvoda/{idProdavnice}/{idProizvoda}/{novaCena}/{novaKolicina}")]
    public async Task<IActionResult> IzmenaProizvoda(int idProdavnice,
                                                    int idProizvoda,
                                                    double novaCena,
                                                    int novaKolicina)
    {
        try
        {
            var prodavnica = await Context.Prodavnice.FindAsync(idProdavnice);
            if (prodavnica == null)
                return BadRequest("Ne postoji prodavnica!");

            var proizvod = await Context.Proizvodi.FindAsync(idProizvoda);
            if (proizvod == null)
                return BadRequest("Ne postoji proizovd!");
            var artikal = await Context.Artikli.Where(p => p.Prodavnica == prodavnica && p.Proizvod == proizvod).FirstOrDefaultAsync();

            if (artikal == null)
                return BadRequest("Prodavnica ne sadrzi taj proizvod!");

            double staraCena = artikal.Cena;
            int staraKolicina = artikal.Kolicina;

            artikal.Cena = novaCena;
            artikal.Kolicina = novaKolicina;

            Context.Artikli.Update(artikal);
            await Context.SaveChangesAsync();

            return Ok($"Promenjen artikal {proizvod.Naziv} u prodavnici {prodavnica.Naziv}\n Cena: {staraCena} -> {artikal.Cena}\nKolicina {staraKolicina} -> {artikal.Kolicina}");
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPut("KupovinaProizvoda/{idProdavnice}/{idProizvoda}/{kolicina}")]
    public async Task<IActionResult> KupovinaProivoda(int idProdavnice, int idProizvoda, int kolicina)
    {
        try
        {
            var prodavnica = await Context.Prodavnice.FindAsync(idProdavnice);
            if (prodavnica == null)
                return BadRequest("Ne postoji prodavnica!");

            var proizvod = await Context.Proizvodi.FindAsync(idProizvoda);
            if (proizvod == null)
                return BadRequest("Ne postoji proizovd!");

            var artikal = await Context.Artikli.Where(p => p.Prodavnica == prodavnica && p.Proizvod == proizvod).FirstOrDefaultAsync();

            if (artikal == null)
                return BadRequest("Prodavnica ne sadrzi taj proizvod!");

            if (artikal.Kolicina < kolicina)
                return BadRequest($"Nedovoljno proizvoda za zeljenu kupovinu! {kolicina} a artikal {artikal.Kolicina} {artikal.Proizvod.ID} {artikal.Prodavnica.ID}");

            artikal.Kolicina -= kolicina;

            Context.Artikli.Update(artikal);
            await Context.SaveChangesAsync();

            return Ok("Uspesno");
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("Istekli")]
    public async Task<IActionResult> Istekli([FromQuery] DateTime datumIsteka, [FromQuery] int[] idProdavnica)
    {
        try
        {

            var result = await Context.Artikli.Where(p => idProdavnica.Contains(p.Prodavnica.ID))
                                                .Where(p => p.Proizvod.RokTrajanja < datumIsteka)
                                                .Include(p => p.Proizvod)
                                                .Select(p => p.Proizvod)
                                                .ToListAsync();

            return Ok(result);
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("SveProdavnice")]
    public async Task<IActionResult> SveProdavnice()
    {
        try
        {
            var prodavnice = await Context.Prodavnice.ToListAsync();
            return Ok(prodavnice);
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("SviProizvodi")]
    public async Task<IActionResult> SviProizvodi()
    {
        try
        {
            var proizvodi = await Context.Proizvodi.ToListAsync();
            return Ok(proizvodi);
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpGet("ProizvodiIzProdavnice/{idProdavnice}")]
    public async Task<IActionResult> ProizvodiIzProdavnice(int idProdavnice)
    {
        try
        {
            var prodavnica = await Context.Prodavnice.FindAsync(idProdavnice);
            if (prodavnica == null)
                return BadRequest("Ne postoji prodavnica sa id " + idProdavnice);

            var artikli = await Context.Artikli.Where(a => a.Prodavnica.ID == idProdavnice)
                                            .Include(a => a.Proizvod).ToListAsync();

            return Ok(artikli.Select(a => new
            {
                ProizvodID = a.Proizvod.ID,
                ProizodNaziv = a.Proizvod.Naziv,
                a.Cena,
                a.Kolicina,
                a.Proizvod.RokTrajanja
            }));
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

}
