// stan + metody = obiekt

// elementy opcjonalne: klasy, dziedziczenie, konstruktory, operator new
// ale nie konieczne by język był obiektowy
var person = {
  name: 'jan',
  say: function () {
    console.log(`${this.name}`);
  }
}

// projektowanie objektowe
// określanie odpowiedzalności i relacji objektów względem siebie
// dobre praktyki, zasady, wzorce
// (-> POO)

// dziedziczenie nie jest konieczne
// dwie korzyści z dziedzczenia:
// 1) oszczędnosć pamięci (klasy i instancje -> delegowanie)
// 2) kontrola typów w trakcie kompilacji
// w javascript 2) nie ma zastowania bo nie ma ścisłej kontroli typów
// (duck typing)

var person = {
  name: 'jan',
  say: function () {
    return this.name;
  }
}
var car = {
  brand: 'skoda',
  say: function () {
    return this.brand;
  }
}
function describe(item) {
  console.log(item.say());
}
describe(person);
describe(car);

// nie potrzebujemy klas i dziedziczenia by język był objektowy
// zyski z dziedziczenia uzyskamy przez (delegacja -> prototypy)

// objektowość prototypowa
// 3 metody tworzenia instancji
// {}, new, Object.create()

// I) {} 
function Person(name, surname) {
  return {
    name: name,
    surname: surname,
    say: function () {
      return `${this.name} ${this.surname}`;
    }
  }
}
var p1 = Person('jan', 'kowalski');
var p2 = Person('adam', 'niezgódka');
console.log(p1.say());

// powielona definicja metody :(
// rozwiązanie -> prototypy
var p = {
  name: 'jan',
  say: function () {
    return this.name;
  }
};

var personProto = {
  surname: 'kowalski',
  say2: function () {
    return this.surname
  }
}

Object.setPrototypeOf(person, personProto);
console.log(person.surname);

// łańcuch prototypów
// null -> jest wartością (ustaloną w objekcie) -> i to zwróć
// undefined -> nie był nigdy zdefiniowany -> idź do prototypu
// can not be cyclic

// Javascript Object.prototype (koniec łańcucha)

// ale to wytrychy
// normalnie stosuje się inne konwencje

// II) new
// każda funkcja może być zawołana z new i bez new
function Foo() {
  this.prop = 1;
  this.say = function () {
    return this.prop;
  }
}
Foo.prototype.say = function () {
  return this.prop;
}

var foo1 = new Foo();
var foo2 = new Foo();
console.log(foo1.say());

// co zmienia new?
// tworzony jest nowy objekt i jest przekazywany do oryginalnej funkcji
// -> funkcja konstruktorowa (z new)
// Foo.prototype -> wspólny objekt

// to znaczy że do protypu po stworzeniu instancji można dodać nową metodę
// (to jak dokompilowanie do klasy metody)
// ale jak z tego w ogóle skorzystać w językach kompilowanych (oprócz refleksji?)

// String.prototype -> do dowolnego objektu możemy dodawać pola (ale też powoduje to nadużycia)

var Person = function (name, surname) {
  this.name = name;
  this.surname = surname;
}
Person.prototype.say = function () {
  return `${this.name} ${this.surname}`;
}
var p = new Person('jan', 'kowalski');
console.log(p.say());

var Worker = function (name, surname, age) {
  // wywołanie bazowej funkcji konstruktorowej
  Person.call(this, name, surname); // call bo przekazuej this
  this.age = age;
}
// Worker.prototype = Person.protype // prawie dobrze
// powiązanie łańcucha prototypów
Worker.prototype = Object.create(Person.prototype);
Worker.prototype.say = function () {
  // "wywołanie metody z klasy bazowej"
  var _ = Person.prototype.say.call(this);
  return `${_} ${this.age}`;
}
var w = new Worker('jan', 'kowalski', 48);
console.log(w.say());

var o = {}
// true
console.log(Object.getPrototypeOf(o) === Object.prototype);
function foo() { }
// true
console.log(Object.getPrototypeOf(foo) === Function.prototype);
var s = 'ala ma kota';
// true
console.log(Object.getPrototypeOf(s) === String.prototype);

// Function.prototype
String.prototype.reverse = function () {
  return this.split('').reverse().join("");
}
console.log('foo bar'.reverse())

// no to może nie trzeba mieć funkcji konstruktorowej
// i mieć czyste prototypy

// III) Object.create()
var person = {
  init: function (name, surname) {
    this.name = name;
    this.surname = surname;
  },
  say: function () {
    return `${this.name} ${this.surname}`;
  }
}
var p = Object.create(person);
// init bo nie jest to funkcja więc nie ma argumentów jak przy new
p.init('jan', 'kowalski'); // funkcja inicjalizacyjna z Pythona
console.log(p.say());

var worker = Object.create(person);
worker.init = function (name, surname, age) {
  // "wywołanie konstruktora klasy bazowej"
  person.init.call(this, name, surname);
  this.age = age;
}
worker.say = function () {
  // "wywołanie metody z klasy bazowej"
  var _ = person.say.call(this);
  return `${_} ${this.age}`;
}
var w = Object.create(worker);
w.init('tomasz', 'malinowski', 48);
console.log(w.say());

// własna implementacja new
var Person = function (name, surname) {
  this.name = name;
  this.surname = surname;
}
Person.prototype.say = function () {
  return `${this.name} ${this.surname}`;
}
// alternatywa dla new f()
// wyrażona przy pomocy Object.create
function New(f, ...args) {
  var _ = Object.create(f.prototype);
  var o = f.apply(_, args);
  if (o)
    return o;
  else
    return _;
}
var p = New(Person, 'jan', 'kowalski');
console.log(p.say());

// własna implementacja ObjectCreate
var person = {
  init: function (name, surname) {
    this.name = name;
    this.surname = surname;
  },
  say: function () {
    return `${this.name} ${this.surname}`;
  }
}
// alternatywa dla Object.create( p )
// wyrażona przy pomocy "new"
function ObjectCreate(p) {
  var f = function () { };
  f.prototype = p;
  return new f();
}
var p = ObjectCreate(person);
p.init('jan', 'kowalski');
console.log(p.say())


// es2016 -> class
// lukier na funkcje konstruktorowe
// super, constructor, extends

class Person1 {
  constructor(name, surname) {
    this.name = name;
    this.surname = surname;
  }
  say() {
    return `${this.name} ${this.surname}`;
  }
}
class Worker1 extends Person1 {
  constructor(name, surname, age) {
    super(name, surname);
    this.age = age;
  }
  say() {
    // "wywołanie metody z klasy bazowej"
    var _ = super.say();
    return `${_} ${this.age}`;
  }
}
var w = new Worker1('tomasz', 'malinowski', 48);
console.log(w.say());

// drzewa binarne
function Tree(val, left, right) {
  this.left = left;
  this.right = right;
  this.val = val;
}
Tree.prototype[Symbol.iterator] = function* () {
  yield this.val;
  if (this.left) yield* this.left;
  if (this.right) yield* this.right;
}
var root = new Tree(1, new Tree(2, new Tree(3)), new Tree(4));
for ( var e of root ) {
  console.log( e );
  }