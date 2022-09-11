var http = require('http');
var express = require('express');
var url = require('url');

var app = express();

app.set('view engine', 'ejs');
app.set('views', '5/zadania/zadanie_4/views');

app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
  res.render('index', { name: '', surname: '', subject_name: '', date: '', subject_group: '', points: new Array(10).fill('') });
});

app.post('/', (req, res) => {
  let name = req.body.name;
  let surname = req.body.surname;
  let subject_name = req.body.subject_name;
  let subject_group = req.body.subject_group;
  let date = req.body.date;
  let points = req.body.points.map(x => {return !x ? 0 : parseInt(x)});
  //console.log(points);

  let sum_points = points.reduce((prev, curr) => {return prev += curr});
  console.log(sum_points);

  if (isFormValid(name, surname, subject_name, subject_group, date)) {
    res.redirect(url.format({
      pathname: '/print',
      query: {
        name: name,
        surname: surname,
        subject_name: subject_name,
        subject_group: subject_group,
        data: date,
        points: points,
        sum_points: sum_points,
      },
    }));
  } else {
    res.render('index', { 
      name: name, 
      surname: surname, 
      subject_name: subject_name, 
      date: date, 
      subject_group: subject_group, 
      points: points, 
      err_fill_msg: "Wypelnij pola: imie, nazwisko, przedmiot, grupa oraz data!"});
  }
});

app.get('/print', (req, res) => {
  // res.query is a dict: (<var_name>: <value>)
  res.render('print', req.query);
});

function isFormValid(name, surname, subject, group, date) {
  // returns false for null, undefined, empty string etc.
  if (!name)
    return false;

  if (!surname)
    return false;

  if (!subject)
    return false;

  if (!group)
    return false;

  if (!date)
    return false;

  return true;
}

var portNum = 8000;
http.createServer(app).listen(portNum);
console.log(`Started the server on port: ${portNum}`);