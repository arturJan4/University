/*
WEPPO - Lista 3, zad 4
Artur Jankowski, indeks: 317928
*/

/*
function createFs(n) { // tworzy tablicę n funkcji
  var fs = []; // i-ta funkcja z tablicy ma zwrócić i
  for ( var i=0; i<n; i++ ) {
    fs[i] =
      function() {
        return i;
      };
    };
    return fs;
  }
*/
/* 1st solution
function createFs(n) { // tworzy tablicę n funkcji
  var fs = []; // i-ta funkcja z tablicy ma zwrócić i
  for ( let i=0; i<n; i++ ) {
    fs[i] =
      function() {
        return i;
      };
    };
    return fs;
  }
*/

/*
let jako lukier syntaktyczny:
*/

let k;

(function(){
  var k;
}());

function createFs(n) { // tworzy tablicę n funkcji
  var fs = []; // i-ta funkcja z tablicy ma zwrócić i
  for ( var i=0; i<n; i++ ) {
    fs[i] =
      function(i) { // korzystamy z własciwości domknięcia
        return function () {
          return i;
        }
      }(i);
    };
    return fs;
  }
var myfs = createFs(10);
  
console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );
  
// 10 10 10
/*

var i wiąże funkcyjnie (a nie blokowo), więc w każdej iteracji pętli
for mamy to samo i, a co za tym idzie funkcja korzysta z tej zmiennej

*/

// babel solution
/*
function createFs(n) {
  // tworzy tablicę n funkcji
  var fs = []; // i-ta funkcja z tablicy ma zwrócić i

  var _loop = function _loop(i) {
    fs[i] = function () {
      return i;
    };
  };

  for (var i = 0; i < n; i++) {
    _loop(i);
  }

  return fs;
}
*/