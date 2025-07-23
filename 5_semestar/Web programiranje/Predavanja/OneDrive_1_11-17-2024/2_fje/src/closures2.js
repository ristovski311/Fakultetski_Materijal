function outer() {
  let a = 4;
  let i = 0;
  const funcArray = [];
  for ( i = 0; i < 5; i++) {
    funcArray[i] = () => {
      a++;
      console.log(i);
      return a;
    }
  }
  return funcArray;
}
const fa = outer();
fa[0]();
fa[1]();
fa[1]();