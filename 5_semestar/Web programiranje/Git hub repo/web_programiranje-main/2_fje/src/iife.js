
// (function (message) {
//     console.log(message);
//   })("hi");

// const makeCounter = (start) =>
//   (function (countStart) {
//     function increase() {
//       countStart++;
//       console.log("inc " + countStart);
//     }

//     function decrease() {
//       countStart--;
//       console.log("dec " + countStart);
//     }
//     return {
//       increase,
//       decrease,
//     };
//   })(start);

// const counter2 = makeCounter(10);
// const counter3 = makeCounter(5);
// counter2.increase();
// counter2.increase();
// counter2.increase();
// counter3.increase();
// counter2.decrease();

























const counterMaker = function(def)
{
 return (function(pocetni){
    function povecaj()
    {
      pocetni++; console.log("c = " + pocetni);
    }
    function smanji()
    {
      pocetni--; console.log("c = " + pocetni);
    }
    return {
      povecaj,
      smanji
    }
  })(def);
}

const broji1 = counterMaker(4);
const broji2 = counterMaker(99);

broji1.povecaj();broji1.povecaj();
broji1.povecaj();
broji1.povecaj();












