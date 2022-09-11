var http = require('http');
var express = require('express');
var app = express();
app.use((req, res, next) => {
  res.write("1");
  next();
  res.write("3");
  res.end();
});
app.use((req, res, next) => {
  res.write("2");
});
http.createServer(app).listen(3000);