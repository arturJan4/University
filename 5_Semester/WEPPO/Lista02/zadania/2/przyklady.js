/*
  użycie operatorów . oraz [] do odwoływania się do składowych obiektuużycie operatorów . oraz [] do odwoływania się do składowych obiektu
*/

let test = { }

test.a = '1'
test['b'] = '2'

console.log(test)

// 1) różnica -> dowolne napisy jako klucze dla operatora []
test['word with whitespace']='42'
// test.word with whitespace
console.log(test)

/*
   2) użycie argumentów innego typu niż string dla operatora [] dostępu do składowej obiektu
*/

// -- Co się dzieje jeśli argumentem operatora jest liczba?
let test2 = {}
test2[1] = 1;
test2['1'] = 42;
console.log(test2) // -> zamienienie na string

// -- Co się dzieje jeśli argumentem operatora jest inny obiekt?
let test3 = {
  //toString: function() {
  //  return "test3"
  //}
}
let test4 = {}
test4[test3] = "obiekt"

console.log(test4); // objekt na napis '[object Object]'

// -- Jaki wpływ na klucz pod jakim zapisana zostanie wartość ma programista w obu przypadkach?
// Można zmodyfikować metodę toString obiektu tak by nazwa zwracana przez tę funkcję była kluczem
// W przypadku liczb konwersja jest wbudowana i (chyba?) nie da się jej zmodyfikować

console.log(test4);

/*
  użycie argumentów innego typu niż number dla operatora [] dostępu do tablicy
*/
// -- Co się dzieje jeśli argumentem operatora jest napis?

let arr = [1,2,3]
console.log(arr["2"]) // -> rzutowanie string->int
arr["3"] = 42
console.log(arr)
arr["napis"] = 42
console.log(arr) // dodawana para key:value jak do obiektu (bo tablica to też objekt)
// czyli przypisujemy property a nie dodajemy element do tablicy
arr[4] = 1
arr[5] = 2
console.log(arr)
console.log(arr['length']) // property call
console.log(arr.length)
// "Length is defined to be one plus the largest numeric index in the array."

// -- Co się dzieje jeśli argumentem operatora jest inny obiekt?
let arr2 = [1,2,3]
arr2[{}] = {}
console.log(arr2)
// podobnie jak wyżej przypisanie jako pole `'[object Object]'` do objektu

// -- Czy i jak zmienia się zawartość tablicy jeśli zostanie do niej dopisana właściwość pod kluczem, który nie jest liczbą?
// nie zmienia się -> zmienia się objekt tablicy

/* -- Czy można ustawiać wartość atrybutu length tablicy na inną wartość niż liczba
elementów w tej tablicy? Co się dzieje jeśli ustawia się wartość mniejszą niż liczba
elementów, a co jeśli ustawia się wartość większą niż liczba elementów?
*/

let arr_test = [1,2,3,4,5]
arr_test['length'] = 2
console.log(arr_test) // ucinamy do długości

arr_test['length'] = 12
console.log(arr_test) // wypełniamy "nowe" pola pustymi elementami