/*
WEPPO - Lista 4, zad 4
Artur Jankowski, indeks: 317928
*/

process.stdout.write("Jak masz na imię?\n");

// attach one-time listener
process.stdin.setEncoding("utf-8");
process.stdin.once('readable', function() {
  let data = process.stdin.read().trim();
  process.stdout.write('Witaj ' + data + '!\n');
  process.exit();
});


process.stdin.once('data', function(data) {
  let name = data.toString().trim();
  process.stdout.write('Witaj ' + name + '!\n');
  process.exit();
});
