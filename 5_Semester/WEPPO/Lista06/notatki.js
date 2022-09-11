// Organizacja kodu (modularność) && programowanie asynchroniczne

// Klasy
// private members
// using closures
function Person(name) {
  var _name;
  this.getName = function () {
    return _name;
  }
  _name = name;
}
var p1 = new Person('jan');
var p2 = new Person('tomasz');
console.log(p1.getName());
console.log(p2.getName());
console.log(p1._name); // brak dostępu

// ale to nie działa w prototypach (bo potrzebujemy zmiennej _name)

// inaczej, przy pomocy symbol
// immedietely invoked function
var Person = (function () {
  // only Person can access nameSymbol
  var nameSymbol = Symbol('name');
  function Person(name) {
    this[nameSymbol] = name;
  }
  Person.prototype.getName = function () {
    return this[nameSymbol];
  };
  return Person;
}());
var p1 = new Person('jan');
var p2 = new Person('tomasz');
console.log(p1.getName());
console.log(p2.getName());
// nie ma sposobu żeby spoza Person dostać się do nameSymbol
// więc nie można z obiektu wydobyć ustawionej wartości

// statyczne -> ez
// namespaces
UWr = {}
UWr.weppo = {};
UWr.weppo.Person = function (name) {
  this.name = name;
}
var p = new UWr.weppo.Person('jan');
console.log(p.name);

// ale w powyższym trzeba uważać by nie nadpisać namespace
// trzebaby więc defensywnie sprawdzać (if(!Uwr)) czy objekty nie są już zdefiniowane
// jak tego uniknąć?:
(function (uwr) {
  uwr.Person = function (name) {
    this.name = name;
  }
})(global.UWr = global.UWr || {});
(function (uwr) {
  uwr.Worker = function (name) {
    this.name = name;
  }
})(global.UWr = global.UWr || {});
var p = new UWr.Person('jan');
var w = new UWr.Worker('Tomasz');
console.log(p.name);
console.log(w.name);

// moduły
// nodejs exports/require
// module.exports -> returns from module
// require('./a')
// but requires caches (so the inside will only execute once)
// cycles :/
// can move require only where it was used
// or set exports line above require line

// docs -> JSDoc
/**
 * This is a function foo
 * @param {number} x this is x
 * @param {string} txt this is a string
 * @returns {number} a sum
 */
function foo(x, txt) {
  return x + txt;
}

x = foo(2, "a");

// Programowanie asynchroniczne
// przerwania -> operacje I/O
// zapytania -> bazy danych

// kontynuacje (callback)
// przeglądarki -> eventListener (np. click)
// pętla zdarzeń

// pomysł:
// wykonujemy kod jednowątkowo
// https://www.youtube.com/watch?v=8aGhZQkoFbQ
// ale korzystamy z kolejki

// setImmediate -> wrzuca na pętlę
// setTimeout -> to samo ale po jakimś czasie
setTimeout(function() {
  setTimeout(function() {
    console.log("3");
  }, 100);
  console.log("2");
}, 2000);

console.log("1");

// fs
// (err, data) pattern
// http (on data, on end) pattern
// can't calls synchronously async functions (return doesn't work)
// use callback instead of return
// callback hell -> nesting
// new Promise -> (resolve, reject)
// .then -> continuation
// continouations chain
// libraries have callback and Promise version
// we want to use Promise version

// async/await -> analogical to yield
// syntactic sugar for continuations
// use try/catch

// code -> notatki