#lang racket
;;wspolnie z Dominik Danelski
;;KOD Z WYKLADU
(define (length xs)
  (define (iter xs n)
    (if (null? xs)
        n
        (iter (cdr xs) (+ n 1))))
  (iter xs 0))

(define (append as bs)
  (if (null? as)
      bs
      (cons (car as)
            (append (cdr as) bs))))

;;KOD WLASCIWY
(define (partition n xs)
  (define (step n xs as bs)
    (cond [(null? xs) (cons as bs)]
          [(<= (car xs) n) (step n (cdr xs) (cons (car xs) as) bs)]
          [else (step n (cdr xs) as (cons (car xs) bs))]))
  (step n xs '() '()))

(define (quicksort xs)
  (cond [(null? xs) xs]
        [(null? (cdr xs)) xs]
        [else
           (let* ([pivot (car xs)]
                  [split (partition pivot xs)])
             (cond [(null? (car split)) (cdr split)]
                   [(null? (cdr split)) (car split)]
                   [else (append (quicksort (car split)) (quicksort (cdr split)))]
                   )
             )]))

(provide partition quicksort)

;;TESTY
(partition 2 (list 1 2 3 4))
(partition 1 (list 1 1 1 4))
(partition 1 (list))

(quicksort (list))
(quicksort (list -1 1))
(quicksort (list 1 1))
(quicksort (list -5 2 3 4 1 2 3 5 6 -5 2))
(quicksort (list 1 2 3 4 5 6 7 8 9 10))
(quicksort (list 10 9 8 7 6 5 4 3 2 1))


