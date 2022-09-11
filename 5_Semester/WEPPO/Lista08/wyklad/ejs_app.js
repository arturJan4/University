var http = require('http');
var express = require('express');
var app = express();
app.set('view engine', 'ejs');
app.set('views', '8/wyklad/views');
app.use((req, res) => {
  res.render('index');
});
http.createServer(app).listen(3000);