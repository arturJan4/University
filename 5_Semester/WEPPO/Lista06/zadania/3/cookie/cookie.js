var http = require('http');
var express = require('express');
var cookieParser = require('cookie-parser');

var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.disable('etag');

app.use(cookieParser('dwe2134ewdoadowdkwkerwe'));
app.use(express.urlencoded({
  extended: true
}));

app.use("/", (req, res) => {
  var cookieValue;
  if (!req.signedCookies.cookie) {
    cookieValue = new Date().toString();
    res.cookie('cookie', cookieValue, { signed: true });
  } else {
    cookieValue = req.signedCookies.cookie;
    res.cookie('cookie', {maxAge: 0});
  }
  res.render("index", { cookieValue: cookieValue });
});

var portNum = 8000;
http.createServer(app).listen(portNum);
console.log(`Started the server on port: ${portNum}`);