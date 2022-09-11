#lang racket
(define (random-sleep)
  (sleep (/ (random) 100)))

;;-------------------------------------
;; ver1
(provide philosopher)
(define (philosopher2 dining-table k)
  (let ([forks (if (= k 4)
                   (cons 0 4)
                   (cons k (modulo (+ k 1) 5)))])  ;;ostatnia osoba podnosi widelce w odwrotnej kolejnosci
  (begin  ((dining-table 'pick-fork) (car forks))
          ((dining-table 'pick-fork) (cdr forks))
          ((dining-table 'put-fork)  (car forks))
          ((dining-table 'put-fork)  (cdr forks)))))
;;-------------------------------------
(provide philosopher)
(define (philosopher dining-table k)
  (let ([forks (if (even? k)
                   (cons k  (modulo (+ k 1) 5))
                   (cons (modulo (+ k 1) 5) k))]) ;; parzyste osoby podnosza w innej kolejnosci
  (begin  ((dining-table 'pick-fork) (car forks))
          ((dining-table 'pick-fork) (cdr forks))
          ((dining-table 'put-fork)  (car forks))
          ((dining-table 'put-fork)  (cdr forks)))))
;;-------------------------------------
(define (test)
  (define table (make-table))
  (run-concurrent
   (lambda() (philosopher table 0))
   (lambda() (philosopher table 1))
   (lambda() (philosopher table 2))
   (lambda() (philosopher table 3))
   (lambda() (philosopher table 4))))

(define (test2)
  (define table (make-table))
  (run-concurrent
   (lambda() (philosopher2 table 0))
   (lambda() (philosopher2 table 1))
   (lambda() (philosopher2 table 2))
   (lambda() (philosopher2 table 3))
   (lambda() (philosopher2 table 4))))
;;-----------------------------------------
;; test
(time (let [(l (build-list 1000 (lambda (_) (test2))))] (void)))
(time (let [(l (build-list 1000 (lambda (_) (test))))] (void)))







