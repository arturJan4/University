
// stack and heap
// passing by value
// kopia wartości dla prostych
// kopia wartości referencji dla objektów złożonych

// changing reference vs changing value that is behind reference
function change(n, p) {
    n = 2;
    // p.a = 2
    p = { a: 2 };
}

n = 1;
p = { a: 1 };
change(n, p);

console.log(n, p);

// Automatic semicolon insertion
function f() {
    return
    {
        var x = 2;
    }
}

// eslint
// npm init
// eslint --init
/*
for (var i = 0; i < 10; i--) {

}
*/

var x = 42;

// printf, String.Format

console.log( `to jest z ${42} napis` );

// trim, startswith, endwith, toLowerCase, toUpperCase, indexOf etc.

// Date, Date.now(), parsing, ISOString -> interoperability

// JSON, JSON.stringify(), JSON.parse()

// getter and setters and properties

var p = {
    a : 1,
    f : function () {
        return 17;
    },
    get bar() {
        return 17;
    },
    set bar(x) {
        p.a = x
    }
}

console.log(p);
console.log(p.bar)
p.bar = 10;
console.log(p);

// adding properties
// adding fields is easy, how to add properties
p.c = 42;

// metaprogramming, reflections
Object.defineProperty(p, "d", {
    value : 1,
    writable : true,
    configurable : true,
});

console.log(p);

// null vs undefined
console.log( p.e );
p.e = 1;
p.e = null;
console.log( p.e );
// how to delete that?
delete p.e;
console.log( p.e );

// arrays are dynamic
var arr = [1,2,3];
arr.push(4);

// arrays are managed dynamically
// arr['100']
// accessing index is similiar because arrays are objects
console.log ( arr[100] );

// arrays are objects ?? -> !!
arr.addit = 42;
console.log(arr);

// it is an object but it contains contigious memory block
// for perforamance reasons

if (arr[100] !== undefined) {

}

// functional interface
console.log( arr.filter( function(x) { return x > 1;}));
console.log( arr.filter ( x => x > 1 ));

console.log( arr.reduce( (prev, curr) => prev + curr, 0));
console.log( arr.join(":") );
console.log( arr.slice(2) ); // does not modify, only returns
console.log( arr.splice(2) ); // modifies and returns original

console.log(arr);
console.log(arr.slice(-1));

var obj = {
    a : 1,
    b : 2
}

arr = [1, 2, 5, 3];

for (var key in p) {
    console.log( key, p[key]);
}

// only iterates through indexes
// iterable
for (var i in arr) {
    console.log(i);
}

// go through values of object
// we can define it for our own objects (make it enumerable)
for (var i of arr) {
    console.log(i);
}

// more: generators etc.

// errors and exceptions
try {
    throw new Error('exc'); // error object
    throw 1; // we can throw everything
}
catch ( e ) {
    console.log( e.message );
}

// ambiguity example
var p = {
    x : 1,
    x : 2
}

function fooo(x, x) {
    console.log(x); // which x to pick
}

// strict mode 
// 'use strict';
var par = {
    x : 1,
    x : 2
}

// asm.js -> generated code
// TBC : functions, closures, generators