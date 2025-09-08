import { createElement } from "./main.js";

export class Proizvod
{
    constructor(id, naziv, cena, kolicina, istek, idProdavnice)
    {
        this.id = id;
        this.naziv = naziv;
        this.istek = istek;
        this.cena = cena;
        this.kolicina = kolicina;
        this.idProdavnice = idProdavnice;
    }

    crtaj(host)
    {
        let proizvodContainer = createElement("proizvod-div", "div", host);
        let nazivLbl = createElement("naziv-proizvoda", "h4", proizvodContainer);
        nazivLbl.innerHTML = this.naziv;    

        let kolicinaLbl = createElement("kolicina-proizvoda", "h3", proizvodContainer);
        kolicinaLbl.innerHTML = this.kolicina;
        this.kolicinaLbl = kolicinaLbl;

        let cenaLbl = createElement("cena-proizvoda", "h4", proizvodContainer);
        cenaLbl.innerHTML = this.cena + " RSD";

        let istekLbl = this.proveriRokTrajanja( proizvodContainer);

        let kupiDugme = createElement("kupi-button", "button", proizvodContainer);
        this.kupiDugme = kupiDugme;
        if(this.kolicina == 0 || istekLbl.innerHTML == "ISTEKAO ROK")
            kupiDugme.disabled = true;


        kupiDugme.innerHTML = "Kupi";
        kupiDugme.onclick = () => this.kupi();
    }

    async kupi()
    {
        console.log(`id ${this.id} prodavnica id  ${this.idProdavnice}`)
        let res = await fetch(`https://localhost:7080/Ispit/KupovinaProizvoda/${this.idProdavnice}/${this.id}/1`, {
            method: "PUT",
            headers: {
                "accept": "*/*"
            }
        })
        if(res.status == 200)
        {
            this.kolicina--;
            if(this.kolicina == 0)
                this.kupiDugme.disabled = true;
            this.kolicinaLbl.innerHTML = this.kolicina;
            console.log(`Promenio sam kolicinu na ${this.kolicina}`);
            console.log(`consolelbl je ` + this.kolicinaLbl.innerHTML)
        }        
        console.log(res.status);
    }

    //3.5h za ovo...

    proveriRokTrajanja(host)
    {
        let now = new Date();
        now.setHours(0, 0, 0, 0);
        console.log(this.istek);
        let istekRoka = new Date(this.istek);
        istekRoka.setHours(0, 0, 0, 0);

        let textToDisplay;
        let istekaoClass;

        if(now > istekRoka)
        {
            textToDisplay = "ISTEKAO ROK";
            istekaoClass = "istekao";
        }
        else
        {
            textToDisplay = "U ROKU";
            istekaoClass = "nije-istekao";
        }

        let istekLbl = createElement("istek-proizvoda", "h5", host);
        istekLbl.innerHTML = textToDisplay;
        istekLbl.classList.add(istekaoClass);

        return istekLbl;
    }
}