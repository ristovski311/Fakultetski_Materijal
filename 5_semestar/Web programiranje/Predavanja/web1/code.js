function spoljna()
{
    let a =10;

    function unutrasnja(x)
    {
        console.log("x+a=" + (x+a));
    }

    unutrasnja(4);
}

//console.log(spoljna());

const student1 =
{
    ime: "Nikola",
    prezime: "Ristovski",
    fakultet: "Elektronski"
}

const koren = function(x) { return Math.sqrt(x);}

const stepen =  x => Math.pow(x,2)

const Zbir = (x,y) => (x+y)

// console.log(Zbir(1,2))
// console.log(koren(16))
// console.log(stepen(12))


const niz = [1,2,3,4,5]

const izmeniParne = x => x.filter(y => y%2 == 0).map(t => t*=2)


//console.log(niz)
//console.log(izmeniParne(niz))

// (
//     function (x)
//     {
//         console.log("hello " + x);
//     }
// )("Nikola")


function brojac (start)
{
    let x = start;

    function increment()
    {
        x++;
    }

    function print()
    {
        console.log(x);
    }

    return{
        increment,
        print
    }
}

let b1 =brojac(10)
let b2 =brojac(10)

// b1.increment();
// b1.print();
// b2.print();
// b2.increment();
// b2.print()


function outer()
{
    let fxArray = [];
    let i = 0
    for(i = 0; i < 5; i++)
    {
        (
            function(i) {
                fxArray.push(
                    () => console.log("i="+i)
                )
            }
        )(i)
    }

    return fxArray
}

// let a = outer();
// a[1]()
// a[3]()


function kreiraj()
{
    let imena = ["Mirko", "Rajko", "Stanko", "Pera", "Mika", "Stana"]

    let i = 0
    for(i = 0; i < imena.length; i++)
    {
        const el = document.createElement("button")
        el.className = "student"
        el.innerText = imena[i]
        document.body.appendChild(el)
        el.addEventListener("click", () => 
        {
            var text = document.createElement("h1")
            text.innerText = ("BOCNULA SI " + el.innerText)
            text.style.color="red";
            document.body.appendChild(text)
        })
    }
}

kreiraj();


