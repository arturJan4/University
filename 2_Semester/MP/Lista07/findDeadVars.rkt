#lang racket
;;Praca wspólna: Dominik Danelski, Artur Jankowski

(provide (struct-out const) (struct-out binop) (struct-out var-expr) (struct-out let-expr) (struct-out var-dead) find-dead-vars)

(struct const    (val)      #:transparent)
(struct binop    (op l r)   #:transparent)
(struct var-expr (id)       #:transparent)
(struct var-dead (id)       #:transparent)
(struct let-expr (id e1 e2) #:transparent)

(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x) (symbol? x)]
    [(var-dead x) (symbol? x)]
    [(let-expr x e1 e2) (and (symbol? x) (expr? e1) (expr? e2))]
    [_ false]))

(define (parse q)
  (cond
    [(number? q) (const q)]
    [(symbol? q) (var-expr q)]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'let))
     (let-expr (first (second q))
               (parse (second (second q)))
               (parse (third q)))]
    [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
     (binop (first q)
            (parse (second q))
            (parse (third q)))]))

; ---------- ;
; Srodowisko ;
; ---------- ;

(define env-empty          (set))
(define (env-add x env)    (set-add env x))
(define (env-lookup x env) (set-member? env x))
(define (env-rmv x env)    (set-remove env x))

; ------------;
; Zadanie     ;
; ------------;
#|
IDEA:
1. find-dead-vars-env zwraca parę <wyrażenie, stan>, aby ten stan mogło wykorzystać wcześniejsze wywołanie rekurencyjne.
2. jeśli zmienna istnieje po prawej stronie binopa to po lewej stronie jest żywa, dlatego najpierw wykonujemy find-dead-vars-env na prawej stronie, tak żeby potem przekazac stan z r do l.
3. wyrażenie let 'x usuwa ze środowiska symbol x, ponieważ poniżej następuje jego przysłonięcie i podobnie jak w przykładzie nowa zmienna może być "martwa" niezależnie od zmiennej o tej samej nazwie zdefiniowanej wcześniej.
4. zmienna jest żywa, jeśli w danym węźle drzewa jest w środowisku, w p.p. jest martwa i dodajemy ją do środowiska, tak aby we wcześniejszych obliczeniach w których ona występuje było wiadomo że znaleźliśmy już ostatnie pod względem wykonywanych obliczeń wystąpienie.
|#

(define (find-dead-vars-env e env)
  (match e
    [(const n) (cons (const n) env)]
    [(binop op l r) (let* ([r1 (find-dead-vars-env r env)]
                           [r2 (find-dead-vars-env l (cdr r1))])
                      (cons (binop op (car r2) (car r1)) (cdr r2)))]
    [(var-expr x) (if (env-lookup x env)
                      (cons (var-expr x) env)
                      (cons (var-dead x) (env-add x env)))]
    [(let-expr x e1 e2) (let* ([r2 (find-dead-vars-env e2 (env-rmv x env))]
                               [r1 (find-dead-vars-env e1 (if (env-lookup x env)
                                                              (env-add x (cdr r2))
                                                              (env-rmv x (cdr r2))))])
     (cons (let-expr x (car r1) (car r2)) (cdr r1)))]))

(define (find-dead-vars e)
  (car (find-dead-vars-env e env-empty)))

"TESTY"
"1:"
(expr? (find-dead-vars (parse '(let (x 3) (+ x x)))))
"2:"
(expr? (find-dead-vars (let-expr 'x (const 3)
                          (binop '+ (var-expr 'x)
                                 (let-expr 'x (const 5)
                                           (binop '+ (var-expr 'x)
                                                     (var-expr 'x)))))))                                 
"3:"
(expr? (find-dead-vars (parse '(+ 2 2))))
"4:"
(expr? (find-dead-vars (parse '(let (x (let (y 2) y)) (+ x y)))))
"5:"
(expr? (find-dead-vars (parse '(+ (let (x 2) x) (let (x 3) x)))))
"6:"
(expr? (find-dead-vars (parse `(let (x 5) (+ (let (x 3) (let (y 2) (+ x y))) (* x x))))))
"7:"
(expr? (find-dead-vars (parse '(let (x (let (y (let (x 2) x)) y)) (+ x 2)))))
"8:"
(expr? (find-dead-vars (parse `(let (x (let (x 4) (+ x x))) (+ (let (x 3) (let (y 2) (+ x y))) (* x x))))))
