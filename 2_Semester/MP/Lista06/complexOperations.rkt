#lang racket
(provide (struct-out complex) parse eval)

;;składnia abstrakcyjna
(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)
(struct i ()           #:transparent)

;;wartości
(struct complex (re im) #:transparent)
(define value?
  complex?)

(define (op->proc op)
  (match op ['+ (lambda (x y) (complex (+ (complex-re x) (complex-re y))
                                       (+ (complex-im x) (complex-im y))))]
            ['- (lambda (x y) (complex (- (complex-re x) (complex-re y))
                                       (- (complex-im x) (complex-im y))))]
            ['* (lambda (x y) (complex (- (* (complex-re x) (complex-re y)) (* (complex-im x) (complex-im y)))
                                       (+ (* (complex-re x) (complex-im y)) (* (complex-re y) (complex-im x)))))]
            ['/ (lambda (x y) (let*([a (complex-re x)]
                                    [b (complex-im x)]
                                    [c (complex-re y)]
                                    [d (complex-im y)]
                                    [den (+ (* c c) (* d d))])
                                   (complex (/ (+ (* a c) (* b d)) den) (/ (- (* b c) (* a d)) den))))]))
(define (eval e)
  (match e
    [(const num) (complex num 0)]
    [(i) (complex 0 1)]
    [(binop op l r) ((op->proc op) (eval l) (eval r))]))

(define (parse q)
  (cond [(number? q) (const q)]
        [(eq? q 'i) (i)]
        [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
         (binop (first q) (parse (second q)) (parse (third q)))]))

"Testy:"
(eval (parse '1))                   ;; 1
(eval (parse 'i))                   ;; i
(eval (parse '(+ (* 2 3) (* 4 5)))) ;; 26
(eval (parse '(+ 2 (* 8 i))))       ;; 2 + 8i
(eval (parse '(+ 2 2)))             ;; 4
(eval (parse '(* i i )))            ;; -1
(eval (parse '(+ 3 (* i 8))))       ;; 3 + 8i
(eval (parse '(* (* i i) (* i i)))) ;; 1
(eval (parse '(- 0 i)))             ;; -i

(eval (parse '(/ (- 7 i) (+ 2 (* 10 i)))))        ;; 1/26 - (9/13)i
(eval (parse '(* (- 4 (* 5 i)) (+ 12 (* 11 i))))) ;; 103 - 16i