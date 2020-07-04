#lang racket

(define (inc n)
  (+ n 1))

;;; tagged lists
(define (tagged-list? len-xs tag xs)
  (and (list? xs)
       (= len-xs (length xs))
       (eq? (first xs) tag)))

;;; ordered elements
(define (make-elem pri val)
  (cons pri val))

(define (elem-priority x)
  (car x))

(define (elem-val x)
  (cdr x))

;;; leftist heaps (after Okasaki)

;; data representation
(define leaf 'leaf)

(define (leaf? h) (eq? 'leaf h))

(define (hnode? h)
  (and (tagged-list? 5 'hnode h)
       (natural? (caddr h))))

(define (make-hnode elem heap-a heap-b)
  (if (< (rank heap-a) (rank heap-b))
      (list 'hnode elem (inc (rank heap-a)) heap-b heap-a)
      (list 'hnode elem (inc (rank heap-b)) heap-a heap-b)))

(define (hnode-elem h)
  (second h))

(define (hnode-left h)
  (fourth h))

(define (hnode-right h)
  (fifth h))

(define (hnode-rank h)
  (third h))

(define (hord? p h)
  (or (leaf? h)
      (<= p (elem-priority (hnode-elem h)))))

(define (heap? h)
  (or (leaf? h)
      (and (hnode? h)
           (heap? (hnode-left h))
           (heap? (hnode-right h))
           (<= (rank (hnode-right h))
               (rank (hnode-left h)))
           (= (rank h) (inc (rank (hnode-right h))))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-left h))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-right h)))))

(define (rank h)
  (if (leaf? h)
      0
      (hnode-rank h)))

;; operations

(define empty-heap leaf)

(define (heap-empty? h)
  (leaf? h))

(define (heap-insert elt heap)
  (heap-merge heap (make-hnode elt leaf leaf)))

(define (heap-min heap)
  (hnode-elem heap))

(define (heap-pop heap)
  (heap-merge (hnode-left heap) (hnode-right heap)))

(define (heap-merge h1 h2)
  (cond
   [(leaf? h1) h2]
   [(leaf? h2) h1]
   [(let ([prio1 (elem-priority (heap-min h1))]
          [prio2 (elem-priority (heap-min h2))])
          (if (< prio1 prio2);;e, h(l), h(r)
              (make-hnode (heap-min h1)
                          (hnode-left h1)
                          (heap-merge (hnode-right h1) h2))
              (make-hnode (heap-min h2)
                          (hnode-left h2)
                          (heap-merge (hnode-right h2) h1))))]))

;;; check that a list is sorted (useful for longish lists)
(define (sorted? xs)
  (cond [(null? xs)              true]
        [(null? (cdr xs))        true]
        [(<= (car xs) (cadr xs)) (sorted? (cdr xs))]
        [else                    false]))
        
 (provide make-elem elem-priority elem-val empty-heap heap-insert heap-merge heap-min heap-pop heap-empty?)

;;TESTY
(make-hnode (make-elem 4 2) leaf leaf)
(make-hnode (make-elem 1 3) leaf leaf)

(heap-merge (make-hnode (make-elem 4 2) leaf leaf) (make-hnode (make-elem 1 3) leaf leaf))

(define myHeap empty-heap)
(define heap1 (heap-insert (make-elem 10 15) empty-heap))
(define heap2 (heap-insert (make-elem 8 1) heap1))
(define heap3 (heap-insert (make-elem 3 2) heap2))
(define heap4 (heap-insert (make-elem 15 3) heap3))
(define heap5 (heap-insert (make-elem 14 7) heap4))
(define heap6 (heap-insert (make-elem 12 6) heap5))
heap6