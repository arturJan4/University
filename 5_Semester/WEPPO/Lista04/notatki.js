// js is functional
// return a function
function a(x) {
  return function () {
    console.log(x);
    x++;
  }
}

x = 5;
foo = a(x);
foo();
foo();
foo();

// accept a function
function b(f) {
  return f();
}

b(() => { console.log("hi") });

// less or more parameters
function more(a, b, c) {
  console.log(a, b, c);
}

more(1); // paramaters are overlooked
more(1, 2, 3, 4, 5);
// we cannot overload functions (because length of arglist doesn't matter)
// can't redefine same identifer functions
// that's also because in global object we have key:value pair for this function

// how to overload then?
function bar(a, b) {
  // we can use if-else and arguments.length
  // with usage of typeof for case type checking

  console.log(a, b);
}

bar(1);
bar('a', 'b');

// we can use default arguments for js
// in new js -> right in declaration
// in old js -> construct b = b || <def value> in code (but it doesn't work for 0)

// we actually don't need formal arguments
function fooo() {
  for (var i = 0; i < arguments.length; i++) {
    console.log(arguments[i]);
  }
}

// introducing rest operator (not spread)
function baar(...tab) {
  for (var i = 0; i < tab.length; i++) {
    console.log(tab[i]);
  }
}

fooo(4, 6, 7)

// returning multiple arguments
// old js -> return array and then user has to use indexes to access
// new js -> destructuring  assignment
function multiple() {
  return [1, 2];
}

var [a, b] = multiple();
// we can use it to swap!

// we can use destructuring  assignment to deal with no-docs needed object passing
function f_obj(p) { // we need comments to understand what p is
  console.log(p.name, p.surname);
}

function b_obj({ name, surname }) {
  console.log(name, surname);
}

var obj_test = {
  name: 'jan',
  surname: 'kowalski'
}

f_obj(obj_test);
b_obj(obj_test);

// Hoising
// variables defined using var can be used before(!) declaration
// because all declarations are moved to top of the file
// also var has functional scope (so we can declare it inside of for-loop)

// to avoid problems js introduced let which is a syntactic sugar
// which we will define later

// Closures -> technically a special arugment which saves the context of a function
// partial applications
function sum(x) {
  return function (y) {
    return x + y;
  }
}

console.log(sum(1)(2));

function sum_all(x) {
  _acc = x;
  var _f = function (y) {
    _acc += y;

    return _f;
  }

  _f.valueOf = function () {
    return _acc;
  }

  return _f;
}
console.log(+sum_all(1)(2)(3)(4));

// memoization (of existing function)
function fib(n) {
  if (n > 1) {
    return fib(n - 1) + fib(n - 2);
  }
  else {
    return 1;
  }
}

function memo(f) {
  var cache = {}

  return function (n) {
    if (cache[n] == undefined) {
      var f_n = f(n);
      cache[n] = f_n;
      return f_n;
    } else {
      return cache[n];
    }
  }
}

var fib_m = memo(fib);

console.log(fib_m(35));
console.log(fib_m(35)); // this is instant
// but if we change to fib_m(34) then it's slow again
// generator trick

var fib = memo(fib)
console.log(fib(1000));

// partial application
function sum2(x, y) {
  return x + y;
}

function partial(fn, ...args) {
  return function (...brgs) {
    return fn(...args, ...brgs);
  }
}

var sum1 = partial(sum2, 1);
console.log(sum1(5));

// currying
function sum3(x, y, z) {
  return x + y + z;
}

//helper function

function rec(fn, n, a) {
  if (n < fn.length) {
    // recursively return one-argument function ...
    return (x) => {
      a.push(x);
      return rec(fn, n + 1, a);
    }
  } else {
    return fn(...a)
  }
}

function curry(fn) {
  return rec(fn, 0, []);
}

console.log(sum3(1, 5, 6));

var sum_r = curry(sum);

console.log(sum_r(1, 5)(6));

//  (Immediately-Invoked Function Expression) 
var counter = (function () {
  var i = 0; // "local" variable

  return {
    get: function () {
      return i;
    },
    increment: function () {
      return ++i;
    }
  };
})();

console.log(counter.get());
counter.increment();
counter.increment();
console.log(counter.get());
// i is hidden outside
// -> and that's exactly how we can implement let

// this in javascript
function test_this() {
  console.log(this.xxxx);
}

var o = {
  xxxx: 1,
  test_this
}

o.test_this(); // 1
var _test_this = o.test_this;
_test_this(); // undefined
_test_this.call(o);

// call -> list of arguments (comma)
// apply -> array            (array)

console.log(test_this.apply(o, [1]));

// bind -> return same function but with context
var _g = _test_this.bind(o); // this is o here
_g();

// e.g. usage: used for Angular scripts
// when we go deep into scope, then we lose this context
// so we either use bind to bind 'this' or use other techniques

// so 'this' is more general in js than in other languages

// Iterators & Generators
// Iterator is a 0-argument function which return an object with only one field
// next which is a functiion with field value and done
function createIterator() {
  var _state = 0;
  return {
    next: function () {
      return {
        value: _state,
        done: _state++ >= 10
      }
    }
  }
}

var it = createIterator();

var _result;
while (_result = it.next(), !_result.done) {
  console.log(_result.value);
}

it = createIterator();
for (var _res; _res = it.next(), !_res.done;) {
  console.log(_res.value);
}

var t = {}

t[Symbol.iterator] = createIterator;

for (var e of t) {

}

// 1:22:45 -> rozwiązanie kolejnego zadania z listy

// Generators take a step further
// analogical to Python's yield
function* createGenerator() {
  for (var i = 0; i < 10; i++) {
    yield i;
  }
}

itt = createGenerator();

for (var _res; _res = itt.next(), !_res.done;) {
  console.log(_res.value);
}

var bar = {
  [Symbol.iterator]: createGenerator
}

for (var b of bar) {
  console.log(b);
}

/* funkcja tworzy węzeł drzewa binarnego 
   z podanej wartości (val), lewego i prawego poddrzewa 
   węzłowi przypisuje funkcję iterującą określoną przez generator 
*/
function createNode(val, left, right) {
  var node = {
    val,
    left,
    right
  };
  node[Symbol.iterator] = nodeIterator(node)
  return node;
}

/* generator iteratora dla przechodzenia drzewa binarnego wgłąb  
   funkcja generatora jeśli ma być użyta do enumeracji for-of 
   (Symbol.iterator) 
   nie może mieć argumentów 
   skorzystamy więc z domknięcia żeby przekazać jej argument przez funkcję 
   w ktorej ją zanurzymy 
*/
function nodeIterator(node) {
  return function* () {
    yield node.val;
    if (node.left) yield* node.left;
    if (node.right) yield* node.right;
  }
}

// twórz drzewo 
//        1 
//       / \ 
//      2   5 
//     / \    
//    3   4    
var root =
  createNode(
    1,
    createNode(
      2,
      createNode(
        3),
      createNode(
        4)
    ),
    createNode(
      5));

console.log("\n")

for (var e of root) {
  console.log(e);
}