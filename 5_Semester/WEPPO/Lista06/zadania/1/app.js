var http = require('http');
var express = require('express');
var multer = require('multer');
const upload = multer({ dest: './uploads' });

var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.get('/', (req, res) => {
  res.render('index');
})

app.post('/uploadfile', upload.single('fileName'), (req, res) => {
  console.log(req.file, req.body);
})

var portNum = 8000;
http.createServer(app).listen(portNum);
console.log(`Started the server on port: ${portNum}`);