#lang racket
;;Praca wspólna: Dominik Danelski, Artur Jankowski
;; ---------------;
;; Jezyk wejsciowy;
;; ---------------;

(struct pos (file line col)     #:transparent)
(struct const    (val)          #:transparent)
(struct binop    (op l r)       #:transparent)
(struct var-expr (id)           #:transparent)
(struct let-expr (loc id e1 e2) #:transparent)

(provide (struct-out const) (struct-out binop) (struct-out var-expr)
         (struct-out let-expr) (struct-out pos) (struct-out var-free)
         (struct-out var-bound) annotate-expression)

(define (expr? e)
  (match e
    [(const n)      (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x)   (symbol? x)]
    [(let-expr loc x e1 e2)
     (and (pos? loc) (symbol? x) (expr? e1) (expr? e2))]
    [_ false]))

(define (make-pos s)
  (pos (syntax-source s)
       (syntax-line   s)
       (syntax-column s)))

(define (parse e)
  (let ([r (syntax-e e)])
    (cond
      [(number? r) (const r)]
      [(symbol? r) (var-expr r)]
      [(and (list? r) (= 3 (length r)))
       (match (syntax-e (car r))
         ['let (let* ([e-def (syntax-e (second r))]
                      [x     (syntax-e (first e-def))])
                 (let-expr (make-pos (first e-def))
                           (if (symbol? x) x (error "parse error!"))
                           (parse (second e-def))
                           (parse (third r))))]
         [op   (binop op (parse (second r)) (parse (third r)))])]
      [else (error "parse error!")])))

; ---------- ;
; Srodowisko ;
; ---------- ;

(struct environ (xs))

(define env-empty (environ null))
(define (env-add x pos env)
  (environ (cons (cons x pos) (environ-xs env))))
(define (env-lookup x env)
  (define (assoc-lookup xs)
    (cond [(null? xs) null]
          [(eq? x (car (car xs))) (cdr (car xs))]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-xs env)))
  
;; --------------- ;
;; Jezyk wyjsciowy ;
;; --------------- ;

(struct var-free  (id)     #:transparent)
(struct var-bound (pos id) #:transparent)

(define (expr-annot? e)
  (match e
    [(const n)         (number? n)]
    [(binop op l r)    (and (symbol? op) (expr-annot? l) (expr-annot? r))]
    [(var-free x)      (symbol? x)]
    [(var-bound loc x) (and (pos? loc) (symbol? x))]
    [(let-expr loc x e1 e2)
     (and (pos? loc) (symbol? x) (expr-annot? e1) (expr-annot? e2))]
    [_ false]))

(define (annotate-expression e)
  (define (start e env)
  (match e
    [(const n) (const n)]
    [(binop op l r) (binop op (start l env) (start r env))]
    [(var-expr x) (let ([pos (env-lookup x env)])
                    (if (null? pos)
                        (var-free x)
                        (var-bound pos x)))]
    [(let-expr loc id e1 e2) (let-expr loc id (start e1 env) (start e2 (env-add id loc env)))]
    [_ (error "Matching error" e)]))
    (start e env-empty))

"Testy"
#|
(annotate-expression (parse #'3))
(annotate-expression (parse #'(* y x)))
(annotate-expression (parse #'(let [x 5] (* y x))))
(annotate-expression (parse #'(let [x 5] (+ (* x x) (let [x 2] x)))))
(annotate-expression (parse #'(let [x (let [x 5] x)] x)))
|#
(expr-annot? (annotate-expression (parse #'3)))
(expr-annot? (annotate-expression (parse #'(* y x))))
(expr-annot? (annotate-expression (parse #'(let [x 5] (* y x)))))
(expr-annot? (annotate-expression (parse #'(let [x 5] (+ (* x x) (let [x 2] x))))))
(expr-annot? (annotate-expression (parse #'(let [x (let [x 5] x)] x))))
