import { Prodavnica } from "./prodavnica.js";
import { Proizvod } from "./proizvod.js";
import { createElement } from "./main.js"

export class App {
    constructor(prodavnice, proizvodi) {
        this.prodavnice = [];
        this.proizvodi = [];

        prodavnice.forEach(prod => {

            let prodavnica = new Prodavnica(prod.id, prod.naziv, prod.adresa, this);
            this.prodavnice.push(prodavnica);
        });

        proizvodi.forEach(pr => {
            this.proizvodi.push(new Proizvod(pr.id, pr.naziv, pr.identifikator))
        })
    }

    async inicProdavnice()
    {
        for(let p of this.prodavnice)
            await p.preuzmiProizvode();
    }

    async crtaj(host) {
        //console.log(this.prodavnice);
        //console.log(this.proizvodi);

        await this.inicProdavnice();

        //console.log(host);

        let formaContainer = createElement("forma-div", "div", host);
        let prodavniceContainer = createElement("prodavnice-div", "div", host);

        this.crtajFormu(formaContainer);
        this.crtajProdavnice(prodavniceContainer);
    }

    crtajFormu(host) {
        let naslov = createElement("naslov-forma", "h2", host);
        naslov.innerHTML = "Dodaj novi proizvod";

        let poljaDiv = createElement("polja-div", "div", host);

        //Kreiramo labele i kontrole

        let nazivDiv = createElement("naziv-div", "div", poljaDiv);
        let nazivLbl = createElement("naziv-labela", "label", nazivDiv);
        nazivLbl.innerHTML = "Naziv:";
        let nazivInput = createElement("naziv-input", "input", nazivDiv);

        let sifraDiv = createElement("sifra-div", "div", poljaDiv);
        let sifraLbl = createElement("sifra-labela", "label", sifraDiv);
        sifraLbl.innerHTML = "Sifra:";
        let sifraInput = createElement("sifra-input", "input", sifraDiv);

        let istekDiv = createElement("istek-div", "div", poljaDiv);
        let istekLbl = createElement("istek-labela", "label", istekDiv);
        istekLbl.innerHTML = "Istek:";
        let istekInput = createElement("istek-input", "input", istekDiv);
        istekInput.type = "date";

        let dodajBtn = createElement("dodaj-button", "button", poljaDiv);
        dodajBtn.innerHTML = "Dodaj";
        dodajBtn.onclick = () => this.dodajProizvod(nazivInput.value, sifraInput.value, new Date(istekInput.value).toISOString());
    }

    async dodajProizvod(naziv, sifra, istek) {

        let danas = new Date().toISOString();

        let res = await fetch("https://localhost:7080/Ispit/DodavanjeProizvoda", {
            method: "POST",
            headers: {
                "accept": "*/*",
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                naziv: naziv,
                identifikator: sifra,
                datumProizvodnje: danas,
                rokTrajanja: istek
            })
        });

        if(res.status == 200)
        {
            let data = await res.json();
            //console.log(data);

            this.proizvodi.push(new Proizvod(data.id, data.naziv, data.identifikator, data.rokTrajanja));
        
            this.prodavnice.forEach(p => p.popuniOpcije());
        }
    }

    crtajProdavnice(host) {
        this.prodavnice.forEach(pr => {
            pr.crtaj(host);
        })
    }

}