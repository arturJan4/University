// easiest signle-threaded dynamic server 
var http = require('http');
var server =
  http.createServer(
    (req, res) => {
      res.setHeader('Content-type', 'text/html; charset=utf-8');
      res.end(`hello world ${new Date()}`);
    });
server.listen(3000);
console.log('started');