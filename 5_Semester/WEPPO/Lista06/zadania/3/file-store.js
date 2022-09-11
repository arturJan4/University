var http = require('http');
var express = require('express');
var session = require('express-session');

var FileStore = require('session-file-store')(session);

var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');

app.disable('etag');

var fileStoreOptions = {};
app.use(session({
  store: new FileStore(fileStoreOptions),
  secret: 'preriedri2342fdk',
  resave: false,
  saveUninitialized: true,
  //cookie: { maxAge: 3600000,secure: false, httpOnly: true }
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