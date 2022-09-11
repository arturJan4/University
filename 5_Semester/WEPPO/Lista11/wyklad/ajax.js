var http = require('http');
var express = require('express');
var ejs = require('ejs');
var multer = require('multer');
var app = express();
var upload = multer();

app.set('views', './views');
app.set('view engine', 'html');

app.engine('html', ejs.renderFile);
app.post('/ajax', upload.single(), (req, res) => {
  var txtParam = req.body.txtParam;
  res.end(`<div>zawartość z serwera ${txtParam}</div>`);
});
app.get('/', (req, res) => {
  res.render('app', { message: 'dynamiczne dane 2' });
});

http.createServer(app).listen(process.env.PORT || 3000);