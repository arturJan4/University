/*
WEPPO - Lista 3, zad 5
Artur Jankowski, indeks: 317928
*/
function sum(...args) {
  return args.reduce((prev, curr) => prev + curr, 0);  
}

console.log(sum(1,2,3));
// 6

console.log(sum(1,2,3,4,5));
// 15