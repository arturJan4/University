/*
WEPPO - Lista 4, zad 5
Artur Jankowski, indeks: 317928
*/

var fs = require('fs');

fs.readFile("4/zadania/5_textfile.txt", "utf-8", function(err, data) {
  if (err) {
    throw err;
  }

  console.log(data);
});