var http = require('http');
var express = require('express');

var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');

app.get('/', (req, res) => {
  var combo = {
    name: 'comboName',
    options: [
      { value: 1, text: 'element 1' },
      { value: 2, text: 'element 2' },
      { value: 3, text: 'element 3' }
    ]
  };

  var checkbox = {
    checkboxes: [
      { id: "name1", name: "name1", text: "test1" },
      { id: "id2", name: "name2", text: "test2" },
      { id: "id3", name: "name3", text: "test3" }
    ]
  };

  var radio = {
    name: 'radioName',
    options: [
      { id: "namer1", value: "radio1", text: "Radio test 1" },
      { id: "namer2", value: "radio42", text: "Radio test 2" }
    ]
  };

  res.render('index', { combo, checkbox, radio });
});

var portNum = 8000;
http.createServer(app).listen(portNum);
console.log(`Started the server on port: ${portNum}`);