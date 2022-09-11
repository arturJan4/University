#lang typed/racket

;;Współpraca : Artur Jankowski, Dominik Danelski

(provide parse typecheck)

(define-type Value  (U Real Boolean))
(define-type Expr   (U const binop var-expr let-expr if-expr))
(define-type Op     (U '+ '- '* '/ '= '> '>= '< '<= 'and 'or))
(define-predicate value? Value)
(define-predicate expr? Expr)
(define-predicate op? Op)

(struct const    ([val : Value])                            #:transparent)
(struct binop    ([op : Op] [l : Expr] [r : Expr])          #:transparent)
(struct var-expr ([id : Symbol])                            #:transparent)
(struct let-expr ([id : Symbol] [e1 : Expr] [e2 : Expr])    #:transparent)
(struct if-expr  ([eb : Expr] [et : Expr] [ef : Expr])      #:transparent)

(: parse (-> Any Expr))
(define (parse q)
  (match q
    [(? real? n) (const n)]
    ['true (const true)]
    ['false (const false)]
    [(? symbol? s) (var-expr s)]
    [`(let (,x ,e1) ,e2)
     #:when (and (symbol? x))
     (let-expr x (parse e1) (parse e2))]
    [`(if ,eb ,et ,ef)
     (if-expr (parse eb) (parse et) (parse ef))]
    [`(,op ,l ,r)
     #:when (op? op)
     (binop op (parse l) (parse r))]))

(: test-parse (-> Expr))
(define (test-parse) (parse '(let [x (+ 2 2)] (+ x 1))))

;------------------------------------------
(define-type EType (U 'real 'boolean))

;;type environment
(define-type TypeEnv environ-T)
(struct environ-T ([xs : (Listof (Pairof Symbol EType))]))

(: tenv-empty TypeEnv)
(define tenv-empty (environ-T null))

(: tenv-add (-> Symbol EType TypeEnv TypeEnv))
(define (tenv-add x v env)
  (environ-T (cons (cons x v) (environ-T-xs env))))

(: tenv-lookup (-> Symbol TypeEnv (U EType #f)))
(define (tenv-lookup x env)
  (: assoc-lookup (-> (Listof (Pairof Symbol EType)) (U EType #f)))
  (define (assoc-lookup xs)
    (cond [(null? xs) #f]
          [(eq? x (car (car xs))) (cdr (car xs))]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-T-xs env)))

;------------------------------------------
;;type eval
;;funkcja pomocnicza dla binop
(: op->type (-> Op (U EType #f) (U EType #f) (U EType #f)))
(define (op->type op left right)
  (if (or (eq? left #f) (eq? right #f))
      #f
      (match op
        [(or '+ '- '* '/)      (if (and (eq? left 'real)    (eq? right 'real))
                                   'real
                                   #f)]
        [(or '= '< '> '<= '>=) (if (and (eq? left 'real)    (eq? right 'real))
                                   'boolean
                                   #f)]
        [(or 'and 'or)         (if (and (eq? left 'boolean) (eq? right 'boolean))
                                   'boolean
                                   #f) ]
        [_  (error "Unrecognized operator" op)])))

(: typecheck-env (-> Expr TypeEnv (U EType #f)))
(define (typecheck-env e env)
  (match e
    [(const n) (if (boolean? n)
                   'boolean
                   'real)]
    [(var-expr x) (tenv-lookup x env)]
    [(binop op l r) (op->type op (typecheck-env l env) (typecheck-env r env))]
    [(let-expr x e1 e2)
     (let ([e1-t (typecheck-env e1 env)])
       (if (eq? e1-t #f)
           #f
           (typecheck-env e2 (tenv-add x e1-t env))))]
    [(if-expr eb et ef)
     (if (eq? (typecheck-env eb env) 'boolean)
         (let ([et-t (typecheck-env et env)]
               [ef-t (typecheck-env ef env)])
           (if (eq? ef-t et-t)
               ef-t
               #f))
         #f)]))

(: typecheck (-> Expr (U EType #f)))
(define (typecheck e)
  (typecheck-env e tenv-empty))

;------------------------------------------
;; Testy
(typecheck (parse '2))
(typecheck (parse 'true))
(typecheck (parse '(< 1 2)))
(typecheck (parse '(if (or (< 2 1) true)
                       (+ 3 2)
                       (+ 4 2))))
(typecheck (parse '(let (x true) (let (y false) (or x y)))))
(typecheck (parse '(let (x 2) (let (y true) (let (x false) (and x y))))))
(typecheck (parse '(= 2 (if (or true false) 5 6))))
(typecheck (parse '(let (x (if
                            (let (x false) (< 1 2))
                            (let (x 2) x) 1)) 2)))

(typecheck (parse '(< 1 true)))
(typecheck (parse '(let (x true) (< 1 x))))
(typecheck (parse '(let (x true) (let (y false) (< x y)))))
(typecheck (parse '(if (or (< 2 true) true)
                       (+ 3 2)
                       (+ 4 2))))
(typecheck (parse '(let (x (if
                            (let (x false) (< 1 2))
                            (let (x false) x) 1)) 2)))
(typecheck (parse '(let (x 1) (let (y true) (let (m (= x y)) y)))))
(typecheck (parse '(if true 1 false)))