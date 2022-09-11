/*
WEPPO - Lista 4, zad 6
Artur Jankowski, indeks: 317928
*/

var readline_m = require('readline');
var fs_m = require('fs');

var reader_interface = readline_m.createInterface(
{
  input: fs_m.createReadStream("4/zadania/6_logfile")
});

// we want 3 clients who did most requests
var ip_dict = {};

reader_interface.on('line', (line) => {
  let ip = line.split(" ")[1]; // 2nd column

  if (ip in ip_dict) {
    ip_dict[ip] = ip_dict[ip] + 1;
  } else {
    ip_dict[ip] = 1;
  }
});

function pop_top(dict) {
  let max_key, max_val = 0;

  for(const [key, value] of Object.entries(dict)) {
    if(value > max_val) {
      max_val = value;
      max_key = key;
    }
  }
  delete ip_dict[max_key];
  return [max_key, max_val];
}

reader_interface.on('close', function() {
  for (let i = 0; i < 3; i++) {
    const [max_key, max_val] = pop_top(ip_dict);
    console.log(max_key, max_val);
  }
});