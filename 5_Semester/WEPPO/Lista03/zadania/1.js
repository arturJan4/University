/*
WEPPO - Lista 3, zad 1
Artur Jankowski, indeks: 317928
*/

let testObj = {
  field: 42,
  method: function() {
    console.log(this.field);
  },
  get gs() {
    return this.field;
  },
  set gs(x) {
    this.field = x;
  }
}

// usage
testObj.method()
console.log(testObj.gs)
testObj.gs = 50
console.log(testObj.gs)

// new fields and methods
testObj['bar'] = 0;
testObj['method2'] = function () {
  console.log('method2 called');
}

testObj.method2();

// new properties can be added only by using defineProperty
Object.defineProperty(testObj, 'val', {
  get : function() {
    return this.bar;
  },
  set : function(i) {
    this.bar = i;
  }
})

testObj.val = 100;
console.log(testObj.val);
