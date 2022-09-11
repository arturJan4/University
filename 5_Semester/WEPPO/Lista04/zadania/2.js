/*
WEPPO - Lista 4, zad 2
Artur Jankowski, indeks: 317928
*/

function Foo() { // funkcja kontruktorowa Foo
  console.log('called Foo!');
}

Foo.prototype.Bar = function() { // publiczna metoda Bar
  function Qux() {
      console.log('called Qux!');
  }
  Qux();
  console.log('called Bar!');
}

let f = new Foo(); // called Foo!
f.Bar(); // called Qux, called Bar

// those 3 are illegal
//f.Bar.Qux();
//f.Bar().Qux();
//f.Qux();

