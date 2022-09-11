module.exports = {
  foo,
  foobar
};

var module_req2 = require('./3_2.js');

function foo(x) {
  console.log(`foo called with ${x}`)
}

function foobar(x) {
  console.log(`foobar called with ${x}`)
  module_req2.bar(x);
}