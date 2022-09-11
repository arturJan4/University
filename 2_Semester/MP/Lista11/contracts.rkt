#lang racket
;Współpraca: Artur Jankowski, Dominik Danelski
(require racket/contract)

(provide (contract-out
          [with-labels with-labels/c]
          [foldr-map foldr-map/c]
          [pair-from pair-from/c]))

(provide with-labels/c foldr-map/c pair-from/c)
;-----------------------------------------
(define with-labels/c
  (parametric->/c [a b] (-> (-> a b) (listof a) (listof (list/c b a)))))

(define (with-labels f xs)
  (if (null? xs)
      null
      (cons (list (f (car xs)) (car xs))
            (with-labels f (cdr xs)))))

;(with-labels 1 (list 1 2))
(with-labels number->string (list 1 2 3))
(with-labels number->string (list))
(with-labels number->string null)
(with-labels number->string `(1))
(with-labels (lambda (x) (if (number? x) (+ x 0) `notnumber)) `(2 `rr 3 5 6))

;-----------------------------------------
(define foldr-map/c
      (parametric->/c [a acc xs]
                  (-> (-> a acc (cons/c xs acc))
                      acc
                      (listof a)
                      (cons/c (listof xs) acc))))

(define (foldr-map f a xs)
  (define (it a xs ys)
    (if (null? xs)
        (cons ys a)
        (let [(p (f (car xs) a))]
          (it (cdr p)
              (cdr xs)
              (cons (car p) ys)))))
  (it a (reverse xs) null))

(foldr-map (lambda (x a) (cons a (+ a x))) 0 '(1 2 3))
(foldr-map (lambda (x a) (cons a (* a x))) 1 '(1 2 3 4))
;-----------------------------------------
(define pair-from/c
  (parametric->/c [x f g] (-> (-> x f) (-> x g) (-> x (cons/c f g)))))

(define (pair-from f g)
  (lambda (x) (cons (f x) (g x))))

((pair-from (lambda (x) x) (lambda (x) x)) 2)
((pair-from (lambda (x) (+ x 1)) (lambda (x) (* x 2))) 2)
;((pair-from (lambda (x y) (+ x y)) (lambda (y) (+ y 1))) 3)  
;-----------------------------------------