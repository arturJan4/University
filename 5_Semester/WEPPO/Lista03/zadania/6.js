/*
WEPPO - Lista 3, zad 6
Artur Jankowski, indeks: 317928
*/

// generator has to return zero-argument function
// so we wrap the return in a function!
function createGenerator(n) {

  return function () {
    var _state = 0;
    return {
      next: function () {
        return {
          value: _state,
          done: _state++ >= n
        }
      }
    }
  }
}

var foo = {
  [Symbol.iterator] : createGenerator(15)
}

for (var f of foo)
{
  console.log(f);
}