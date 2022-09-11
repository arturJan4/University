var http = require('http');
var express = require('express');
var session = require('express-session');

var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');

app.disable('etag');
app.use(session({
  resave: true, saveUninitialized: true, secret:
    'dsdwe2e2ewewse'
}));

app.use("/", (req, res) => {
  var sessionValue;
  if (!req.session.sessionValue) {
    sessionValue = "session: " + new Date().toString();
    req.session.sessionValue = sessionValue;
  } else {
    sessionValue = req.session.sessionValue;
    req.session.destroy();
  }
  res.render("index", { sessionValue: sessionValue });
});

var portNum = 8000;
http.createServer(app).listen(portNum);
console.log(`Started the server on port: ${portNum}`);