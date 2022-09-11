var fs = require('fs')
var util = require('util')

fs.readFile("4/zadania/5_textfile.txt", "utf-8", function(err, data) {
  if (err) {
    throw err;
  }

  console.log(data);
});

// return Promise object
function fspromise(path, encoding) { 
  return new Promise((resolve, reject) => { 
      fs.readFile(path, encoding, (err, data) => { 
          if (err) 
              reject(err); 
          else
            resolve(data); 
      }); 
  }); 
} 

fspromise('4/zadania/5_textfile.txt', 'utf-8') 
  .then( data => { 
      console.log(data); 
  }) 
  .catch( err => { 
    console.log(`error: ${err}`); 
});

// promisify (&& async)
(async function() {
const _f = util.promisify(fs.readFile);
let res = await _f('4/zadania/5_textfile.txt', 'utf-8');
console.log(res);
})();

// promises
(async function() {
let val = await fs.promises.readFile('4/zadania/5_textfile.txt', 'utf-8')
console.log(val)
})();
