var bcrypt = require('bcrypt');
(async function () {
  // hasło użytkownika
  var password = 'Foo.Bar.123';
  var rounds = 12;
  var hash = await bcrypt.hash(password, rounds);
  // wynik hashowania zapisuje się w bazie danych
  console.log(hash);
  // weryfikacja
  var attemptedPassword = 'Foo.Bar';
  var result = await bcrypt.compare(attemptedPassword, hash);
  console.log(result); // false
  attemptedPassword = 'Foo.Bar.123';
  result = await bcrypt.compare(attemptedPassword, hash);
  console.log(result); // true
})();