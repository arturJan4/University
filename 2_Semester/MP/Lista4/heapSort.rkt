#lang racket
(provide heapsort) (require "leftist.rkt")

(define (heapsort xs)
  (define myHeap empty-heap);;pusty stos na poczatek
  (define (heapsort-pop heap);;pop-uje elementy
    (if (heap-empty? heap)
         null
        (cons (elem-val (heap-min heap))
              (heapsort-pop (heap-pop heap)))))
  (define (heapsort-build listEl heap);;dodaje elementy na stos
    (if (null? listEl)
        (heapsort-pop heap);;po konczeniu dodawania usuwamy elementy
        (heapsort-build (cdr listEl) 
                        (heap-insert (make-elem (car listEl) (car listEl)) heap))))
  (heapsort-build xs myHeap))


;;TESTY
(define (sorted? xs)
  (cond [(null? xs)              true]
        [(null? (cdr xs))        true]
        [(<= (car xs) (cadr xs)) (sorted? (cdr xs))]
        [else                    false]))
;;jak budowac liste losowych elementow
;;źródło fragmentu: https://stackoverflow.com/questions/40497748/building-a-random-list
(define (randomlist n mx)
  (cond
    [(= n 0) empty]
    [else
     (cons (+ 1 (random mx))
           (randomlist (- n 1) mx))]))
;;

(define (reverseList n)
  (cond
    [(= n 0) empty]
    [else
     (cons n
           (reverseList (- n 1)))]))

(define (sortedList n)
  (define (rec acc n)
    (cond [(> acc n) null]
          [else (cons acc (rec (+ acc 1) n))]))
  (rec 1 n))

(define test1 (randomlist  10 100))
(define test2 (randomlist  10000 1000))
(define test3 (sortedList  10000))
(define test4 (reverseList 10000))

test1
(display "->")
(sorted? (heapsort test1))

;;przypadki brzegowe
(display "pusta: ")
(sorted? (heapsort (list)))
(display "1-elementowa: ")
(sorted? (heapsort (list 0)))
(display "obciazeniowy (10tys el.) losowych: ")
(sorted? (heapsort test2))

;;
(display "10 tys posortowane: ")
(sorted? (heapsort test3))
(display "10 tys odwrotnie posortowane: ")
(sorted? (heapsort test4))
