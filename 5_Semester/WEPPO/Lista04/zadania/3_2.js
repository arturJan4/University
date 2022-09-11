module.exports = {
  bar,
};

var module_req1 = require('./3_1.js');

function bar(x) {
  console.log(`bar called with ${x}`);
  module_req1.foobar(x);
}