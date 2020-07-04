#lang racket
;;KOD Z WYKLADU
(define (length xs)
  (define (iter xs n)
    (if (null? xs)
        n
        (iter (cdr xs) (+ n 1))))
  (iter xs 0))
;;KOD

(define (merge as bs)
  (cond [(null? as) bs]
        [(null? bs) as]
        [(> (car as) (car bs)) (cons (car bs) (merge as (cdr bs)))]
        [else (cons (car as) (merge (cdr as) bs))]))

(define (split as)
  (let ([middlePoint (floor (/ (length as) 2))])
    (cons (take as middlePoint) (list-tail as middlePoint))))

(define (mergesort as)
  (cond [(null? as) as]
        [(null? (cdr as)) as]
        [else
         (let ([splitList (split as)])
              (merge (mergesort (car splitList))
                     (mergesort (cdr splitList))))
        ]))

(provide merge split mergesort)

;;TESTY
(split (list))
(split (list 1 2 3 4))

(merge (list) (list))
(merge (list 1 2) (list 3 4))
(mergesort (list))
(mergesort (list 42))
(mergesort (list 0 5 2 3 -1 -5 5 5 3 3))
(mergesort (list 10 5 10))