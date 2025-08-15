async function getRandomNumber() {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      const number = Math.ceil(Math.random() * 10);
      resolve(number);
    }, 1000);
  });
}

async function getAsyncArray() {
  const n = [];
  n[0] = await getRandomNumber();
  n[1] = await getRandomNumber();
  n[2] = await getRandomNumber();
  return n;
}

(async () => {
  const seq = getAsyncArray(); // start sequential
  const par = Promise.all([
    getRandomNumber(),
    getRandomNumber(),
    getRandomNumber()
  ]); // start parallel

  console.log("brojevi " + (await seq));   // wait for sequential
  console.log("brojevi u paraleli " + (await par)); // wait for parallel
})();