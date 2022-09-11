var l = require('lodash')

var a = 1;
var b = 1;

console.log(a+b);

var c = "foo";

var obj = {};
obj.foo = "hello"; // obj["foo"]
obj.bar = 42;

console.log(obj);
console.log(obj.not_defined); // null, undefined

var p = {
	toString: function () {
		return '17';
	},
}

var q = {
	valueOf: function () {
		return 9;
	},
}

q[p] = 144;
console.log( Object.keys(q) );
console.log( p + q);

// variables and boxing & unboxing
// referencje object (new Number) vs simple typle (Number)

// logical operators, &&, ||, !
// dynamic conversions -> ez mistakes

// dynamic conversions -> non-intuitive but idomatic code
var def = a || 1; // 1 is a default value

// non idiomatic solutions
var def_bad1;
if (a) {
	def_bad1 = a
} else {
	def_bad1 = 1
}

if (a != null) {

}

var def_bad2 = a ? a : 1 

// behaviour puzzle
var p = {};

console.log( p );
console.log( !p );
console.log( !p+[] ); // 'false'+''

console.log( [] );
console.log( +[] ); // 0

console.log ( (!p+[])[+[]] ); // f

// instaceof, typeof - differences
// typeof returns type
// instance of used in logic comparisions
console.log( typeof a );
console.log( a instanceof Number);

// == (loose) vs === (strict)

var a = 0
console.log( a == false );
console.log( a === false );