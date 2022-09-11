#lang racket

;;Współpraca : Artur Jankowski, Dominik Danelski
(provide lcons lnull lnull? lcar lcdr)

(define (lcons x f)
  (mcons x f))

(define lnull null)

(define lnull? null?)

(define (lcar xs)
  (mcar xs))

(define (lcdr xs)
  (if (mpair? (mcdr xs)) (mcdr xs) (begin (set-mcdr! xs ((mcdr xs))) (mcdr xs))))

(define (test-len xs n)
  (if (mpair? (mcdr xs)) (test-len (mcdr xs) (+ n 1)) n))

(define (from n)
  (mcons n (lambda() (from (+ n 1)))))

;;Testy

(let ((test (lcdr (lcdr (from 5))))) test)
(let ((test2 (from 5)))
  (begin (writeln (mcar test2)) (writeln (mcdr test2)) (writeln (test-len test2 0)) (lcdr test2) (writeln (mcdr test2)) (test-len test2 0)))


(define nats
  (from 0))

(define (lnth n xs)
  (cond [(= n 0) (lcar xs)]
        [else (lnth (- n 1) (lcdr xs))]))

(define (lfilter p xs)
  (cond [(lnull? xs) lnull]
        [(p (lcar xs))
         (lcons (lcar xs) (lambda () (lfilter p (lcdr xs))))]
        [else (lfilter p (lcdr xs))]))

(define (prime? n)
  (define (factors i)
    (cond [(>= i n) (list n)]
          [(= (modulo n i) 0) (cons i (factors (+ i 1)))]
          [else (factors (+ i 1))]))
  (= (length (factors 1)) 2))

(define primes (lfilter prime? (from 2)))

(lnth 1 primes)
(lnth 2 primes)
(define test-list (from 0))
(lcdr test-list)
(lcdr test-list)
test-list

(lnth 0 primes)           ;;2,
(time (lnth 1000 primes)) ;;7927
(time (lnth 1001 primes)) ;;7933
(time (lnth 1002 primes)) ;;7937

"Testy struktury:"
(let ((test (lcdr (lcdr (from 5))))) test)
(let ((test2 (from 5)))
  (begin (writeln (mcar test2))
         (writeln (mcdr test2))
         (writeln (test-len test2 0))
         (lcdr test2) (writeln (mcdr test2))
         (test-len test2 0)))
