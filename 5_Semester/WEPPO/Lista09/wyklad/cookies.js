var http = require('http');
var express = require('express');
var cookieParser = require('cookie-parser');

var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.disable('etag'); // caching
app.use(cookieParser());
app.use(express.urlencoded({
  extended: true
}));

app.use("/", (req, res) => {
  var cookieValue;
  if (!req.cookies.cookie) {
    cookieValue = new Date().toString();
    res.cookie('cookie', cookieValue);
  } else {
    cookieValue = req.cookies.cookie;
  }
  res.render("index", { cookieValue: cookieValue });
});

http.createServer(app).listen(3000);