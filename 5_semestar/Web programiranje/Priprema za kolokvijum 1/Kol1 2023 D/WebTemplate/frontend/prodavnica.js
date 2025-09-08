import { createElement } from "./main.js";
import { Proizvod } from "./proizvod.js";

export class Prodavnica{
    constructor(id, naziv, adresa, app)
    {
        this.id = id;
        this.naziv = naziv;
        this.adresa = adresa;
        this.proizvodi = [];
        this.app = app;
    }

    async preuzmiProizvode()
    {
        let proz = await fetch(`https://localhost:7080/Ispit/ProizvodiIzProdavnice/${this.id}`).then(res => res.json()).catch(console.log("Greska"));
    
        console.log("PROZIVODI")
        console.log(proz);

        proz.forEach(proz => {
            this.proizvodi.push(new Proizvod(proz.proizvodID, proz.proizodNaziv, proz.cena, proz.kolicina, proz.rokTrajanja, this.id))
        });

        console.log("PROIZVODI PRODAVNICE")
        console.log(this.proizvodi)
    }

    crtaj(host)
    {
        let prodavnicaContainer = createElement("prodavnica-container", "div", host);

        let headingProdavnice = createElement("heading-prodavnice", "div", prodavnicaContainer);
        let naslovProdavnice = createElement("naslov-prodavnice", "h2", headingProdavnice);
        naslovProdavnice.innerHTML = this.naziv;

        let adresaProdavnice = createElement("adresa-prodavnice", "h4", headingProdavnice);
        adresaProdavnice.innerHTML = this.adresa;

        let prodavnicaContent = createElement("content-prodavnice-div", "div", prodavnicaContainer);

        let sadrzajProdavniceContainer = createElement("sadrzaj-prodavnice-div", "div", prodavnicaContent);
        this.crtajSadrzaj(sadrzajProdavniceContainer);
        this.sadrzajProdavniceContainer = sadrzajProdavniceContainer;
        let formaProdavniceContainer = createElement("forma-div", "div", prodavnicaContent);
        this.crtajFormu(formaProdavniceContainer);


    }

    crtajSadrzaj(host)
    {
        console.log(this.proizvodi);
        this.proizvodi.forEach(p => {
            p.crtaj(host);
        })
    }

    crtajFormu(host)
    {
        let naslov = createElement("naslov-forma", "h2", host);
        naslov.innerHTML = "Dodaj artikle prodavnici";

        let poljaDiv = createElement("polja-div", "div", host);

        //Kreiramo labele i kontrole

        let nazivDiv = createElement("naziv-div", "div", poljaDiv);
        let nazivLbl = createElement("naziv-labela", "label", nazivDiv);
        nazivLbl.innerHTML = "Naziv:";
        let nazivSelect = createElement("naziv-input", "select", nazivDiv);
        this.nazivSelect = nazivSelect;

        this.popuniOpcije();

        //KOLICINA JE CENA

        let kolicinaDiv = createElement("kolicina-div", "div", poljaDiv);
        let kolicinaLbl = createElement("kolicina-labela", "label", kolicinaDiv);
        kolicinaLbl.innerHTML = "Cena:";
        let kolicinaInput = createElement("kolicina-input", "input", kolicinaDiv);
        kolicinaInput.type = "number";

        let dodajBtn = createElement("dodaj-button", "button", poljaDiv);
        dodajBtn.innerHTML = "Dodaj";
        dodajBtn.onclick = () => this.dodajArtikle(kolicinaInput.value);
        
    }

    async dodajArtikle(cena)
    {
        let res = await fetch(`https://localhost:7080/Ispit/DodavanjeArtikla/${this.nazivSelect.value}/${this.id}/${cena}`, {
            method: "POST",
            headers: {
                "accept": "*/*"
            }
        })

        if(res.status == 200)
        {
            let data = await res.json();
            console.log("AAA");
            console.log(data);
            this.proizvodi.push(new Proizvod(data.id, data.naziv, data.naziv, data.cena, 10, data.rokTrajanja, this.id))

            this.sadrzajProdavniceContainer.innerHTML = "";
            this.crtajSadrzaj(this.sadrzajProdavniceContainer);
        }
        else
            console.log("Greska kod dodavanja artikla")
    }

    popuniOpcije()
    {
        this.nazivSelect.innerHTML = "";
        this.app.proizvodi.forEach(p => {
            let opcija = createElement("opcija", "option", this.nazivSelect);
            opcija.innerHTML = p.naziv;
            opcija.value = p.id;
        })
    }
}