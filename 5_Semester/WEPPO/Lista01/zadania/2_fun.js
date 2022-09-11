
function sumDigits(number) {
	let sum = 0;
	while(number) {
	    sum += number % 10;
	    number = Math.floor(number / 10);
	}
	return sum;
    
}
    
function divisibleDigits(number) {
	let i = number;
	while(i) {
	    digit = i % 10;
	    if((digit == 0) || (number % digit != 0)) {
		return false;
	    }
	    i = Math.floor(i / 10);
	}
    
	return true;
}
    
solution = [];
for (let i = 1; i <= 100000; i += 1) {
	if((i % sumDigits(i) == 0) && divisibleDigits(i)) {
	    solution.push(i);
	}
}
    
console.log(solution);