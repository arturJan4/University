/*
  operator instanceof to predykat zwracający wartość boolowską.
  Zwraca true jeśli dany objekt jest sprawdzanego typu.
  (Sprawdza czy objekt został utworzony danym konstruktorem)
*/

console.log("test" instanceof String) // typ prymitywny
console.log(new String("test") instanceof String) // objektowa wersja typu
console.log(new String("test") instanceof Object) // dziedziczenie
console.log(1 instanceof String)
console.log(new Number(1) instanceof Number)

/*
  operator typeof zwraca łańcuch reprezentujący typ danego wyrażenia.
  To może być łańcuch znaków, zmienna, słowo kluczowe lub objekt
  (typ prymitywny (undefined, null, boolean, string oraz number) lub object)
*/

console.log(typeof "test")
console.log(typeof new String("test"))
console.log(typeof 1)
