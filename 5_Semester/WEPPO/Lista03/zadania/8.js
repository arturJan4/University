/*
WEPPO - Lista 3, zad 8
Artur Jankowski, indeks: 317928
*/

function *fib() {
  let [f_fst, f_snd] = [0, 1];
  while(true) {
    yield f_fst;
    [f_fst, f_snd] = [f_snd, f_snd + f_fst]; 
  }
}

// generator function 
// "Calling a generator function does not execute its body immediately; an iterator object for the function is returned instead. 
// When the iterator's next() method is called, the generator function's body is executed until the first yield expression, 
// which specifies the value to be returned from the iterator or, with yield*, delegates to another generator function. "

// "The next() method returns an object with a value property containing the yielded value and a done property which indicates 
// whether the generator has yielded its last value, as a boolean."

// "Calling the next() method with an argument will resume the generator function execution, replacing the yield expression where 
// an execution was paused with the argument from next()."

function *take(it, top) {
  for (let i = 0; i < top; i++) {
    yield it.next().value
  }
}

for (let num of take( fib(), 10) ) {
  console.log(num);
}