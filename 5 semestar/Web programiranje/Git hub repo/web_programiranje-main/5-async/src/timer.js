

function timer() {
    // callback hell
    setTimeout(() => {
        console.log("😎 1");
        setTimeout(() => {
            console.log("😎 2");
        }, 1000)
    }, 1000)
}

function loop() {
    let counter = 0;
    // iako je 1ms, nece da se izvrsi dok se while petlja ne okonca
    setTimeout(() => {
        console.log("done");
    }, 1)
    while(counter < 100000){ 
        console.log(counter);   
        counter++;
    }

}

function getRandomNumber()
{
    return () => 
    setTimeout(() => {
        const x = Math.floor(Math.random() * 10);
        console.log(`Random number is ${x}`);
    },3000);
}

const niz = [];
niz.push(getRandomNumber());
niz.push(getRandomNumber());
niz.push(getRandomNumber());
niz.push(getRandomNumber());
niz.push(getRandomNumber());

niz.forEach((e) => e());

//timer();
//loop();
//getRandomNumber();