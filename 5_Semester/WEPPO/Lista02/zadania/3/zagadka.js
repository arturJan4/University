console.log( (![]+[])[+[]]+(![]+[])[+!+[]]+([![]]+[][[]])[+!+[]+[+[]]]+(![]+[])[!+[]+!+[]] );

// wypisuje "fail"
// podzielmy na grupy pomiędzy '+' (bo mamy objekt i indeks ()[])

// (![]+[])[+[]]
console.log((![]+[])[+[]])

/*
  ![] == false
  ![]+[] == "false" (operator + zamienia false na sting i dodajemy pusty napis)
  +[] == 0 (konwersja [] na int)
  (![]+[])[+[]] == "false"[0] == 'f'
*/

// (![]+[])[+!+[]]
console.log((![]+[])[+!+[]])

/*
  ![]+[] == false
  !+[] == true // negacja zero to true
  +!+[] == 1   // + konwertuje true na int (1)
  (![]+[])[+!+[]] == "false"[1] == 'a'
*/

// ([![]]+[][[]])[+!+[]+[+[]]]
console.log(([![]]+[][[]])[+!+[]+[+[]]])

/*
  [![]] == [false]
  [][[]] == undefined (element [[]] tablicy [])
  [![]]+[][[]] == falseundefined (rzutowanie na string obu tablic i konkatenacja)
  [+[]] == []
  +!+[] == 1
  +!+[] + [+[]] == '10'
  ([![]]+[][[]])[+!+[]+[+[]]] == "falseundefined"[10] == 'i'
*/


// (![]+[])[!+[]+!+[]]
console.log((![]+[])[!+[]+!+[]])

/*
  ![]+[] == false
  (!+[])+(!+[]) == 2 (true + true -> 1 + 1)
  (![]+[])[!+[]+!+[]] == false[2] == 'l'
*/