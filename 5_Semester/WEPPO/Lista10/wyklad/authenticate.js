var http = require('http');
var express = require('express');
var cookieParser = require('cookie-parser');
var app = express();

app.use(express.urlencoded({ extended: true }));
app.use(cookieParser('sgs90890s8g90as8rg90as8g9r8a0srg8'));
app.set('view engine', 'ejs');
app.set('views', './views');

/**
*
* @param {http.IncomingMessage} req
* @param {http.ServerResponse} res
* @param {*} next
*/
function authorize(req, res, next) {
  // user is signed in
  if (req.signedCookies.user) {
    req.user = req.signedCookies.user;
    next();
  } else {
    res.redirect('/login?returnUrl=' + req.url);
  }
}

// we can pass multiple middlewares comma-separated
// wymaga logowania dlatego strażnik – middleware „authorize”
app.get('/', authorize, (req, res) => {
  res.render('app', { user: req.user });
});
app.get('/logout', authorize, (req, res) => {
  res.cookie('user', '', { maxAge: -1 });
  res.redirect('/')
});

// strona logowania
app.get('/login', (req, res) => {
  res.render('login');
});

// check login form (password storing/passing is really not safe here!)
app.post('/login', (req, res) => {
  var username = req.body.txtUser;
  var pwd = req.body.txtPwd;
  if (username == pwd) {
    // wydanie ciastka
    res.cookie('user', username, { signed: true });
    // przekierowanie
    var returnUrl = req.query.returnUrl;
    res.redirect(returnUrl);
  } else {
    res.render('login', { message: "Zła nazwa logowania lub hasło" }
    );
  }
});

http.createServer(app).listen(3000);
console.log('serwer działa, nawiguj do http://localhost:3000');