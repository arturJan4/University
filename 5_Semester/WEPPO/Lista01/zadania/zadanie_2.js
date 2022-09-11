/*
WEPPO - Lista 1, zad 2
Artur Jankowski, indeks: 317928
*/

let solution = [];

for (let i = 1; i <= 100000; i += 1) {
    let sum = 0;
    let isDivisible = true;

    let number = i;
    while (number) {
        digit = number % 10;
        if ((digit == 0) || (i % digit != 0)) {
            isDivisible = false;
            break;
        }

        sum += digit;
        number = Math.floor(number / 10);
    } 

    if (isDivisible && (i % sum == 0)) {
        solution.push(i);
    }
}

console.log(solution) // 763