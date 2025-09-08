import {App} from './app.js'

let prodavnice = await fetch("https://localhost:7080/Ispit/SveProdavnice").then(res => res.json());

let proizvodi = await fetch("https://localhost:7080/Ispit/SviProizvodi").then(res => res.json());

let app = new App(prodavnice, proizvodi);

await app.crtaj(document.body);

export function createElement(klasa, tip, host)
{
    let el = document.createElement(tip);
    el.classList.add(klasa);
    host.appendChild(el);
    return el;
}

//console.log(prodavnice);
//console.log(proizvodi);