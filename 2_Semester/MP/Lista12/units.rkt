#lang racket
;;Praca wspólna : Artur Jankowski i Dominik Danelski
(require "graph.rkt")
(provide bag-stack@ bag-fifo@)

;; struktura danych - stos
(define-unit bag-stack@
  (import)
  (export bag^)

  (define (bag-list x) (cadr x))
  (define (bag-make xs) (list 'bag xs))
  
  (define (bag? x)
    (and (list? x)
         (list? (bag-list x))
         (eq? (length x) 2)
         (eq? (car x) 'bag)))

  (define (bag-empty? x)
    (empty? (bag-list x)))
  
  (define empty-bag
    (bag-make '()))

  (define (bag-insert xs x)
    (bag-make (cons x (bag-list xs))))

  (define (bag-peek x)
    (car (bag-list x)))

  (define (bag-remove x)
    (if (bag-empty? x)
        (error "stack jest pusty")
        (bag-make (cdr (bag-list x)))))
  )

;; struktura danych - kolejka FIFO
(define-unit bag-fifo@
  (import)
  (export bag^)

  (define (bag-in x) (second x))
  (define (bag-out x) (third x))
  (define (bag-make in out)
    (if (null? out)
        (list 'bag '() (reverse in))
        (list 'bag in out)))

  (define (bag? x)
    (and (list? x)
         (list? (bag-in x))
         (list? (bag-out x))
         (eq? (length x) 3)
         (eq? (car x) 'bag)))
  
  (define (bag-empty? x)
    (and (null? (bag-in x)) (null? (bag-out x))))

  (define empty-bag
    (list 'bag '() '()))

  (define (bag-insert xs x)
    (bag-make (cons x (bag-in xs)) (bag-out xs)))
  
  (define (bag-peek x)
    (car (bag-out x)))
  
  (define (bag-remove x)
    (bag-make (bag-in x) (cdr (bag-out x))))
  )

;; otwarcie komponentów stosu i kolejki

(define-values/invoke-unit bag-stack@
  (import)
  (export (prefix stack: bag^)))

(define-values/invoke-unit bag-fifo@
  (import)
  (export (prefix fifo: bag^)))

;; testy w Quickchecku
(require quickcheck)

;; testy kolejek i stosów
(define-unit bag-tests@
  (import bag^)
  (export)
  
  (define (list->bag xs)
    (if (null? xs)
        empty-bag
        (bag-insert (list->bag (cdr xs)) (car xs))))
  (define (bag->list bag)
    (if (bag-empty? bag)
        null
        (cons (bag-peek bag) (bag->list (bag-remove bag)))))
  
  ;; test przykładowy: jeśli do pustej struktury dodamy element
  ;; i od razu go usuniemy, wynikowa struktura jest pusta
  (quickcheck
   (property ([s arbitrary-symbol])
             (bag-empty? (bag-remove (bag-insert empty-bag s)))))
  ;; peek na jednoelementowej strukturze zwraca ten sam element
  (quickcheck
   (property ([s arbitrary-symbol])
             (eq? s (bag-peek (bag-insert empty-bag s)))))
  ;; elementy mogą się powtarzać w ramach listy
  (quickcheck
   (property ([s arbitrary-symbol])
             (eq? s (bag-peek (bag-remove (bag-insert (bag-insert empty-bag s) s))))))
  ;; zachowana jest długość listy
  (quickcheck
   (property ([xs (arbitrary-list arbitrary-symbol)])
             (let ((bag (list->bag xs)))
               (equal? (length xs) (length (bag->list bag))))))
          
  )

;; uruchomienie testów dla obu struktur danych

(invoke-unit bag-tests@ (import (prefix stack: bag^)))
(invoke-unit bag-tests@ (import (prefix fifo: bag^)))

(define-unit bag-fifo-tests@
  (import bag^)
  (export)

  (define (list->bag xs)
    (if (null? xs)
        empty-bag
        (bag-insert (list->bag (cdr xs)) (car xs))))
  (define (bag->list bag)
    (if (bag-empty? bag)
        null
        (cons (bag-peek bag) (bag->list (bag-remove bag)))))
        
  ;;wrzucenie różnych elementów x, y  w tej kolejności na kolejkę
  ;;i następnie usunięcie elementu i ponowne wrzucenie y zmienia kolejkę
  (quickcheck
   (property ([x arbitrary-symbol]
              [y arbitrary-symbol])
             (==> (not (equal? x y))
             (let* ([QueFirst (bag-insert (bag-insert empty-bag x) y)]
                    [QueSecond (bag-insert (bag-remove QueFirst) y)])
             (not (equal? QueFirst QueSecond))))))
  ;;wrzucenie i wyjecie z kolejki odwraca listę
  (quickcheck
   (property ([xs (arbitrary-list arbitrary-symbol)])
             (let ((bag (list->bag xs)))
               (equal? xs (reverse (bag->list bag))))))
  ;;pierwszy wrzucony element zawsze będzie wyjęty jako pierwszy (FIFO)
  (quickcheck
   (property ([xs (arbitrary-list arbitrary-symbol)])
             (==> (not (null? xs))
                  (equal? (last xs) (bag-peek (list->bag xs))))))               
  )
(invoke-unit bag-fifo-tests@ (import (prefix fifo: bag^)))

(define-unit bag-stack-tests@
  (import bag^)
  (export)

  (define (list->bag xs)
    (if (null? xs)
        empty-bag
        (bag-insert (list->bag (cdr xs)) (car xs))))
  (define (bag->list bag)
    (if (bag-empty? bag)
        null
        (cons (bag-peek bag) (bag->list (bag-remove bag)))))
        
  ;;wrzucenie różnych elementów x, y  w tej kolejności na stos
  ;;i następnie usunięcie elementu i ponowne wrzucenie y nie zmienia stosu
  (quickcheck
   (property ([x arbitrary-symbol]
              [y arbitrary-symbol])
             (==> (not (equal? x y))
             (let* ([StackFirst (bag-insert (bag-insert empty-bag x) y)]
                    [StackSecond (bag-insert (bag-remove StackFirst) y)])
             (equal? StackFirst StackSecond)))))
  ;;wrzucenie i wyjęcie ze stosu zachowuje kolejność listy
  (quickcheck
   (property ([xs (arbitrary-list arbitrary-symbol)])
             (let ((bag (list->bag xs)))
               (equal? xs (bag->list bag)))))
  ;;ostatni wrzucony element zawsze będzie wyjęty jako pierwszy (LIFO)
  (quickcheck
   (property ([xs (arbitrary-list arbitrary-symbol)]
              [elem arbitrary-symbol])
             (eq? elem (bag-peek (bag-insert (list->bag xs) elem)))))
  )
(invoke-unit bag-stack-tests@ (import (prefix stack: bag^)))

;; otwarcie komponentu grafu
(define-values/invoke-unit/infer simple-graph@)

;; otwarcie komponentów przeszukiwania 
;; w głąb i wszerz
(define-values/invoke-unit graph-search@
  (import graph^ (prefix stack: bag^))
  (export (prefix dfs: graph-search^)))

(define-values/invoke-unit graph-search@
  (import graph^ (prefix fifo: bag^))
  (export (prefix bfs: graph-search^)))

;; graf testowy
(define test-graph
  (graph
   (list 1 2 3 4)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4))))
(define test-graph2 ;;brak krawedzi
  (graph
   `(list 1 2)
   `()))
(define test-graph3 ;;wyspy
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 2)
         (edge 2 1)
         (edge 3 4)
         (edge 4 5))))
(define test-graph4 ;;cykl
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 2)
         (edge 2 3)
         (edge 3 4)
         (edge 4 5)
         (edge 5 1))))
(define test-graph5
  (graph
   (list 1 2)
   (list (edge 1 2))))
(define test-graph6
  (graph
   (list 0 1 2 3 4 5 6 9 10 15)
   (list (edge 0 1) (edge 0 3) (edge 0 5)
         (edge 1 2) (edge 1 4)
         (edge 3 6) (edge 3 9)
         (edge 5 10) (edge 5 15))))

;; uruchomienie przeszukiwania na przykładowym grafie
(bfs:search test-graph 1)
(dfs:search test-graph 1)
(bfs:search test-graph 2)
(dfs:search test-graph 2)
(bfs:search test-graph 0)
(dfs:search test-graph 0)

(bfs:search test-graph2 1)
(dfs:search test-graph2 1)

(bfs:search test-graph3 1)
(dfs:search test-graph3 1)
(bfs:search test-graph3 3)
(dfs:search test-graph3 3)
(bfs:search test-graph3 4)
(dfs:search test-graph3 4)

(bfs:search test-graph4 1)
(dfs:search test-graph4 1)

(bfs:search test-graph5 1)
(dfs:search test-graph5 2)

(bfs:search test-graph6 0)
(dfs:search test-graph6 0)