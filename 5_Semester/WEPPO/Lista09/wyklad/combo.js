var http = require('http');
var express = require('express');
var cookieParser = require('cookie-parser');

var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.disable('etag'); // caching

app.use("/", (req, res) => {
  res.render("combobox");
});

http.createServer(app).listen(3000);