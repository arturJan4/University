/*
WEPPO - Lista 3, zad 7
Artur Jankowski, indeks: 317928
*/

function fibiter() {
  let [f_fst, f_snd] = [0, 1];
  return {
    next: function() {
      let val = f_fst;
      [f_fst, f_snd] = [f_snd, f_snd + f_fst]; 
      return {
        value: val,
        done: false
      }
    }
  }
}

function *fib() {
  let [f_fst, f_snd] = [0, 1];
  while(true) {
    yield f_fst;
    [f_fst, f_snd] = [f_snd, f_snd + f_fst]; 
  }
}

// var _it = fibiter();
var _it = fib()
let iter_limit = 20;

for ( var _result; _result = _it.next(), !_result.done;) {
  if (iter_limit <= 0) {
    break;
  }
  iter_limit--;

  console.log( _result.value );
}

/* działa
for ( var i of fib() ) {
  console.log( i );
}
*/

/* nie działa
for ( var i of fibiter ) {
  console.log( i );
}
*/

/*
// ale to już działa
// jest "Iterable"

const iterable = {
  [Symbol.iterator] : fibiter
}

for ( var i of iterable) {
  console.log( i );
}
*/
