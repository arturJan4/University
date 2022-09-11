/*
WEPPO - Lista 1, zad 5
Artur Jankowski, indeks: 317928
*/

function fib_rec(n) {
	if (n < 2) {
        return n;
    }

    return fib_rec(n-1) + fib_rec(n-2);
}

function fib_iter(n) {
    let [f_fst, f_snd] = [0, 1]

    if (n < 2) {
        return n;
    }

    for (let i = 2; i <= n; i++) {
        [f_fst, f_snd] = [f_snd, f_snd + f_fst];  
    }

    return f_snd;
}

const n = 42;

function measureTime(func, n, label) {
    console.time(label);
    func(n);
    console.timeEnd(label);
}

function createTable() {
    for (let i = 10; i <= n; i++) {
        measureTime(fib_rec, i, i + ": fib_rec");
        measureTime(fib_iter, i, i + ": fib_iter");
    }
}

createTable();