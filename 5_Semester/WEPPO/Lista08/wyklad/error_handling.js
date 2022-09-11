var http = require('http');
var express = require('express');
var app = express();
app.use((req, res, next) => {
  if (true) // jakiś warunek błędu
    next("description");
  else
    res.end("poprawne działanie");
});
app.use((err, req, res, next) => {
  res.end(`Error handling request: ${err}`);
});
http.createServer(app).listen(3000);
