#lang racket

;;kod wzorowany na przykladzie z podrecznika
(define (square x) (* x x))
(define (cube x) (* x x x))
(define (abs x)
  (if (< x 0) (- x) x))
 
(define (cube-root x)
  (define (good-enough? current)
    (< (abs (- (cube current) x)) 0.00001));;0.00001 = epsilon
  (define (improve current)
    (/ (+ (/ x (square current)) (* 2 current)) 3));(x/(y^2) + 2y)/3
  (define (cube-root-iter current)
    (if (good-enough? current)
        current
        (cube-root-iter (improve current))))
  (cube-root-iter 1.0))

(provide cube-root)

;;TESTY
(cube-root 0);;0
(cube-root 1);;1
(cube-root 1000);;10
(cube-root 27);;3
(cube-root (- 27));;-3
(cube-root 74088);;42
(cube-root (- 74088));;42
(cube-root (/ 1 27));;(1/3)
