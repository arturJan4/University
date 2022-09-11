#lang racket
(provide (struct-out const) (struct-out binop) rpn->arith)
;; -------------------------------
;; Wyrazenia w odwr. not. polskiej
;; -------------------------------

(define (rpn-expr? e)
  (and (list? e)
       (pair? e)
       (andmap (lambda (x) (or (number? x) (member x '(+ - * /))))
               e)))

;; ----------------------
;; Wyrazenia arytmetyczne
;; ----------------------

(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)

(define (arith-expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r)
     (and (symbol? op) (arith-expr? l) (arith-expr? r))]
    [_ false]))

;; ----------
;; Kompilacja
;; ----------

;;stos z wykladu
(struct stack (xs))
(define empty-stack (stack null))
(define (empty-stack? s) (null? (stack-xs s)))
(define (top s) (car (stack-xs s)))
(define (push a s) (stack (cons a (stack-xs s))))
(define (pop s) (stack (cdr (stack-xs s))))

(define (rpn->arith e)
  (define (start e tempStack)
  (cond [(null? e) (top tempStack)];;wypisz stos
        [(number? (car e))
         (start (cdr e) (push (const (car e)) tempStack))] ;;dodaj liczbę do stosu
        [(member (car e) '(+ - * /))
         (let ([element (binop (car e) (top (pop tempStack)) (top tempStack))]) ;;element = operacja i dwa poprzednie elementy
              (start (cdr e) (push element (pop (pop tempStack)))))] ;;dodaj element do stosu
        [else (error "compilation error")]))
  (start e empty-stack))

;;pomocnicze do testów (z wykładu)
(define (arith->rpn e)
  (match e
    [(const n) (list n)]
    [(binop op l r) (append (arith->rpn l)
                            (arith->rpn r)
                            (list op))]))
(define (parse q)
  (cond [(number? q) (const q)]
        [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
         (binop (first q) (parse (second q)) (parse (third q)))]))

"Testy:"
(arith-expr? (rpn->arith '(1 2 * 3 4 * +)))
;;sprawdzamy czy funkcja jest "odwrotna" do funkcji z wykładu
;;(equal? (parse x) (rpn->arith (arith->rpn (parse x))))
(equal? (parse '(* (+ 2 2) 2)) (rpn->arith (arith->rpn (parse '(* (+ 2 2) 2)))))
(equal? (parse '(+ (* 2 3) (* 4 5))) (rpn->arith (arith->rpn (parse '(+ (* 2 3) (* 4 5))))))
(equal? (parse '1) (rpn->arith (arith->rpn (parse '1))))
(equal? (parse '(- 3 2)) (rpn->arith (arith->rpn (parse '(- 3 2)))))