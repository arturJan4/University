/*
WEPPO - Lista 3, zad 3
Artur Jankowski, indeks: 317928
*/

function forEach( a, f ) {
  for (let i = 0; i < a.length; i++) {
    f(a[i]);
  }
}

function map( a, f ) {
  let res = [];
  for (let i = 0; i < a.length; i++) {
    res.push(f(a[i]));
  }
  return res;
}
function filter( a, f ) {
  let res = [];
  for (let i = 0; i < a.length; i++) {
    if (f(a[i])) {
      res.push(a[i]);
    }
  }
  return res;
}

var a = [1,2,3,4];

console.log(a);

forEach( a, _ => { console.log( _ ); } );
// [1,2,3,4]

console.log(filter( a, _ => _ < 3 ));
// [1,2]

console.log(map( a, _ => _ * 2 ));
// [2,4,6,8]

function inc(x) {
  return x + 1;
}

function square(x) {
  return x * x;
}

console.log(map(map(a, inc), square))
console.log(filter(map(a, _ => square(_)), _ => _ % 2 == 1))
