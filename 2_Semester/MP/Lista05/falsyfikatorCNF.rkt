#lang racket
;WSPÓŁPRACA JAKUB PRZYDATEK, DAWID DUDEK, ARTUR JANKOWSKI
(require "props.rkt")
(provide falsifiable-cnf?)

(define (lit? f)
  (or (var? f)
      (and (neg? f)
           (var? (neg-subf f)))))

(define (lit-pos v)
  v)

(define (lit-neg v)
  (neg v))

(define (lit-var l)
  (if (var? l)
      l
      (neg-subf l)))

(define (lit-pos? l)
  (var? l))

(define (to-nnf f)
  (cond
    [(var? f)  (lit-pos f)]
    [(neg? f)  (to-nnf-neg (neg-subf f))]
    [(conj? f) (conj (to-nnf (conj-left f))
                     (to-nnf (conj-right f)))]
    [(disj? f) (disj (to-nnf (disj-left f))
                     (to-nnf (disj-right f)))]))

(define (to-nnf-neg f)
  (cond
    [(var? f)  (lit-neg f)]
    [(neg? f)  (to-nnf (neg-subf f))]
    [(conj? f) (disj (to-nnf-neg (conj-left f))
                     (to-nnf-neg (conj-right f)))]
    [(disj? f) (conj (to-nnf-neg (disj-left f))
                     (to-nnf-neg (disj-right f)))]))

(define (mk-cnf xss)
  (cons 'cnf xss))

(define (clause? f)
  (and (list? f)
       (andmap lit? f)))

(define (cnf? f)
  (and (pair? f)
       (eq? 'cnf (car f))
       (list? (cdr f))
       (andmap clause? (cdr f))))

(define (to-cnf f)
  (define (join xss yss)
    (apply append (map (lambda (xs) (map (lambda (ys) (append xs ys)) yss)) xss)))
  (define (go f)
    (cond
      [(lit? f)  (list (list f))]
      [(conj? f) (append (go (conj-left f))
                         (go (conj-right f)))]
      [(disj? f) (join (go (disj-left f))
                       (go (disj-right f)))]))
  (mk-cnf (go f)))


; kilka obserwacji:
; -jeśli w klauzuli jest p oraz neg p to klauzula jest tautologią możemy zatem zrobić dwie listy -
;  w jednej trzymać zmienne, a w drugiej zmienne z negacji(czyli z (neg p) wezmiemy p)
; -jesli jakaś zmienna występuje w dwóch listach to klauzula jest tautologią w.p.p. jest falsyfikowalna
; -jeśli jakaś klauzula nie jest tautologią to cala formuła w cnf nie jest
; -jeśli wszystkie klauzule sa tautologiami to cała formuła w cnf jest
; -jeśli chcemy znaleźć wartościowanie które falsyfikuje klauzulę to musimy przejść po dwóch listach
;  i wybrać wartościowanie które falsyfikowałoby literały więc
;  z listy zmiennych bez negacji bierzemy zmienną i dajemy jej wartość f
;  z listy w której były zmienne zanegowane bierzemy zmienną i dajemy jej wartość t (wtedy jej negacja da f)

(define (falsifiable-cnf? form)
    (define (divide-clause clause) ;dzieli klauzule na liste zmiennych bez negacji i z negacja
    (define (divide-clause-op clause not-negative negative)
    (if (empty? clause)
        (cons not-negative negative)
        (if (var? (car clause))
            (divide-clause-op (cdr clause)
                           (cons (car clause) not-negative)
                            negative)
            (divide-clause-op (cdr clause)
                            not-negative
                           (cons (neg-subf (car clause)) negative)))))
    (divide-clause-op clause (list) (list)))
  
  (define (in-list? el l) ;sprawdza czy element jest na liscie
    (if (empty? l)
        #f
        (if (eq? (car l) el)
            #t
            (in-list? el (cdr l)))))
            
  (define (check-for-tautology l1 l2) ;sprawdza czy jedna zmienna w obu listach
    (if (empty? l1)
        #f
        (if (in-list? (car l1) l2)
            #t
            (check-for-tautology (cdr l1) l2))))
  
  (define (eval-positive-negative positive negative);;buduje liste wartosciwan
    (define (eval-positive l score)
    (if (empty? l)
        score
        (eval-positive (cdr l)
                       (cons (list (car l) #f) score))))
    (define (eval-negative l score)
    (if (empty? l)
        score
        (eval-negative (cdr l)
                       (cons (list (car l) #t) score))))
    (eval-negative negative (eval-positive positive (list))))
  
  (define (check-clause clause);;sprawdza czy klazula jest tautologia jesli nie to zwraca wartosciowanie falsyfikujace
    (define positive-and-negative (divide-clause clause)) ;tworzy pare list z literalami z negacja i tymi bez negacji
    (if (check-for-tautology (car positive-and-negative)  ;(car - positive, cdr - negative)
                             (cdr positive-and-negative)) 
        #f
        (eval-positive-negative (car positive-and-negative)
                                (cdr positive-and-negative))))
  
  (define (check-form form)
    (if (empty? form)
        #f ;tautologia
        (let ([wynik-check-clause (check-clause (car form))])
        (if (eq? wynik-check-clause #f)
            (check-form (cdr form))
            wynik-check-clause))))
  
    (check-form (cdr (to-cnf (to-nnf form))))) ;chce odsiac "smiecia" w postaci napisu 'cnf

"TESTY"
(falsifiable-cnf? (disj 'p (neg 'p)))                           ;; #f
(falsifiable-cnf? 'p)                                           ;; (p #f)
(falsifiable-cnf? (disj (conj 'p 'q) (conj (neg 'p) 'q)))       ;; (p #f) (q #f)
(falsifiable-cnf? (conj (disj 'p (neg 'p)) (disj (neg 'q) 'q))) ;; #f
(falsifiable-cnf? (conj (conj (conj 'p (neg 'p)) 'q) (neg 'q))) ;; (p #f)
(falsifiable-cnf? (neg (neg 'p)))                               ;; (p #f)
(falsifiable-cnf? (disj (neg (neg 'p)) (neg 'p)))               ;; #f
(falsifiable-cnf? (disj (conj 'p (neg 'q)) (neg 'p)))           ;; (q #t) (p #t)
(falsifiable-cnf? (neg (conj 'p (neg 'p))))                     ;; #f
(falsifiable-cnf? (neg (conj 'p (conj (neg 'p) 'q))))           ;; #f

; algorytm działa szybciej od standardowego, ponieważ działa w czasie wielomianowym, a nie wykładniczym(dla n zmiennych 2^n możliwych wartościowań).
; przeanalizujmy dokładnie jego złożoność:
; divide-clause działa liniowo względem ilości literałów w klauzuli
; in-list działa liniowo względem ilosci elementów w liście
; check-for-tautology działa kwadratowo - na każdym elemenencie powtarza liniową ilość razy wiec dostajemy O(n^2)
; eval-positive-negative działa liniowo względem ilości literałów w klauzuli
; check-clause działa kwadratowo, bo wywołuje niezależnie check-for-tautology(O(n^2)) i eval-positive-negative(O(n))
; check-form moze dzialac szesciennie bo moze wywolac dla kazdej klauzuli funkcje ktora dziala kwadratowo
; zatem czas działania funkcji w najgorszym razie powinien być sześcienny(w pesymistycznym przypadku dlugiej klauzuli literałow na wejściu np. phi = p1 | p2 | ... | pn)