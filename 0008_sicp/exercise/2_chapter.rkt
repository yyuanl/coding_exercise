#lang sicp
;最大公约数
(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))
(define (abs x)
  (if (or (= x 0) (> x 0))
      x
      (- 0 x)))

;有理数表示
(define (combined-pos-rat? a b)
  (> (* a b) 0))
(define (make-rat n d)
  (let ((t-gcd (gcd (abs n)(abs d)))
        (t-pos? (> (* n d) 0)))
    (let ((final-n (if t-pos?
                       (/ (abs n) t-gcd)
                       (- 0 (/ (abs n) t-gcd))))
          (final-d (/ (abs d) t-gcd)))
      (cons final-n final-d))))
    
  
(define (numer x) (car x))
(define (denom x) (cdr x))
(define (daoshu x) (make-rat (denom x) (numer x)))
;加减乘除、是否相等
(define (add-rat x y)
  (make-rat (+ (* (numer x) (denom y)) (* (numer y) (denom x)))
            (* (denom x)(denom y))))
(define (sub-rat x y)
  (make-rat (- (* (numer x) (denom y)) (* (numer y) (denom x)))
            (* (denom x) (denom y))))

(define (mul-rat x y)
  (make-rat (* (numer x)(numer y))
            (* (denom x)(denom y))))
(define (div-rat x y)
  (mul-rat x (daoshu y)))

(define (equal-rat? x y)
  (= (* (numer x)(denom y))
     (* (numer y)(denom x))))
;打印
(define (print-rat x)
  (newline)
  (display (numer x))
  (display "/")
  (display (denom x)))

;测试
(define one-half (make-rat 1 2))
(define one-third (make-rat 1 3))
(define (test)
  (print-rat one-half)
  (print-rat one-third)
  (print-rat (add-rat one-half one-third))
  (print-rat (sub-rat one-half one-third))
  (print-rat (mul-rat one-half one-third))
  (print-rat (div-rat one-half one-third))
  (print-rat (add-rat one-third one-third))
  (print-rat (sub-rat one-third one-half)))

;ex2.2 平面上线段的表示
(define (make-segment start-point end-point)
  (cons start-point end-point))

(define (start-segment x)
  (car x))
(define (end-segment x)
  (cdr x))
(define (make-point x y)
  (cons x y))
(define (x-point poit)
  (car poit))
(define (y-point poit)
  (cdr poit))

(define (midpoint-segment segment)
  (define (average a b) (/ (+ a b) 2.0))
  (make-point (average (x-point (start-segment segment)) (x-point (end-segment segment)))
              (average (y-point (start-segment segment)) (y-point (end-segment segment)))))

(define (print-point p)
  (newline)
  (display "(")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ")"))

(define p1 (make-point 2 8))
(define p2 (make-point 4 9))
(define p1tp2 (make-segment p1 p2))

(define (test-segment)
  (print-point (midpoint-segment p1tp2)))

;ex2.7
(define (make-interval a b) (cons a b))
(define (upper-bound x) (max (car x)
                             (cdr x)))
(define (lower-bound x) (min (car x)
                             (cdr x)))
(define (add-interval x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
                 (+ (upper-bound x) (upper-bound y))))

(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))
 (define (div-interval x y) 
   (if (let ((te (* (lower-bound y)(upper-bound y))))
         (or (< te 0) (= te 0))) 
       (error "Division error (interval spans 0)" y) 
       (mul-interval x  
                     (make-interval (/ 1. (upper-bound y)) 
                                    (/ 1. (lower-bound y)))))) 
(define (print-interval x)
  (newline)
  (display "[")
  (display (lower-bound x))
  (display ",")
  (display (upper-bound x))
  (display "]"))
;ex2.8
(define (sub-interval x y)
  (make-interval (- (lower-bound x)
                    (upper-bound y))
                 (- (upper-bound x)
                    (lower-bound y))))
(define i (make-interval 2 3))
(define j (make-interval -1 3))

;ex 2.17
(define (append list1 list2)
  (if (null? list1)
      list2
      (cons (car list1) (append (cdr list1) list2))))
(define (last-pair iterms)
  (if (null? (cdr iterms))
      (car iterms)
      (last-pair (cdr iterms))))
  
(define (reverse iterms)
  (if (null? iterms)
      nil
      (append (reverse (cdr iterms))
             (list (car iterms)))))

(define (test217)
  (reverse (list 1 2 3 4)))

;ex2.20
(define (even? x)
  ( = (remainder x 2) 0 ))
(define (odd? x)
  (not (even? x)))
(define (same-parity x . y)
  (define (f filter a-list result)
    (if (null? a-list)
        result
        (f filter (cdr a-list) (if (filter (car a-list))
                           (append result (list (car a-list)))
                           result))))
  (let ((properity (if (even? x)
                       even?
                       odd?)))
    (f properity y nil)))

;ex2.21
(define (map proc item)
  (if (null? item)
      nil
      (cons (proc (car item))
            (map proc (cdr item)))))

(define (square-list items)
  (define (adouble x) (* x x))
  (if (null? items)
      nil
      (cons (adouble (car items))
            (square-list (cdr items)))))
(define (square-list-map items)
  (map (lambda (x) (* x x))
       items))


(define (test221)
  (square-list-map (list 1 2 3 4)))
(define xx (list 1 2 3))
(define yy (list 4 5 6))

;ex2.27
(define (deep-reverse alist-227)
  (if (not (pair? alist-227))
      alist-227
      (append (deep-reverse (cdr alist-227))
              (list (deep-reverse (car alist-227))))))
(define x227 (list (list 1 2)
                   (list 3 4)))

;ex2.28
(define (fringe lst)
  (cond ((null? lst) lst)
        ((not (pair? lst))(list lst))
        (else (append (fringe (car lst))
                      (fringe (cdr lst))))))
(define (fringe-1 lst)
  (if (not (pair? lst))
      (list lst)
      (append (fringe (car lst))
              (fringe (cdr lst)))))
(define x228 (list (list 1 2)(list 3 4)))
;ex2.30
(define (square-tree-rec tre)
  (cond ((null? tre) nil)
        ((not (pair? tre)) (* tre tre))
        (else (cons (square-tree-rec (car tre))
                    (square-tree-rec (cdr tre))))))
(define (square-tree-map tre)
  (map (lambda (sub-tree)
         (if (pair? sub-tree)
             (square-tree-map sub-tree)
             (* sub-tree sub-tree)))
       tre))
(define x230 (list 1
                   (list 2
                         (list 3 4)
                         5)
                   (list 6 7)))

;ex2.32
(define (square-tree232 tree)
  (tree-map square tree))
(define (square x) (* x x))
(define (tree-map proc tree)
  (map (lambda (sub-tree)
         (if (pair? sub-tree)
             (tree-map proc sub-tree)
             (proc sub-tree)))
       tree))


;ex2.40
 (define (filter predicate sequence) 
   (cond ((null? sequence) nil) 
         ((predicate (car sequence)) 
          (cons (car sequence)  
                (filter predicate (cdr sequence)))) 
         (else (filter predicate (cdr sequence))))) 
(define (enumerate-interval low high) 
  (if (> low high) 
      nil 
      (cons low (enumerate-interval (+ low 1) high))))
(define (accumulate op initial sequence) 
  (if (null? sequence) 
      initial 
      (op (car sequence) 
          (accumulate op initial (cdr sequence)))))
(define (flatmap proc seq) 
  (accumulate append nil (map proc seq)))

(define (unique-pairs n)
  (flatmap (lambda (hi)
             (map (lambda (lo)
                    (list lo hi))
                  (enumerate-interval 1 (- hi 1))))
           (enumerate-interval 1 n)))

;ex2.41
(define (three-num n)
  (flatmap (lambda (k)
             (map (lambda (ij)
                    (append ij (list k)))
                  (unique-pairs (- k 1))))
           (enumerate-interval 1 n)))

(define (sum=s n s)
  (filter (lambda (lst)
            (= (accumulate + 0 lst) s))
          (three-num n)))
;ex2.42 八皇后问题
(define empty-board nil)
(define (make-coor x y) (list x y))
(define (x-lst coor)(car coor))
(define (y-lst coor)(car (cdr coor)))
(define (slope a b)
  (/ (- (y-lst b)(y-lst a))
     (- (x-lst b)(x-lst a))))


(define (col-same? x y)
  (= (y-lst x) (y-lst y)))
(define (slope-abs=1? coor1 coor2)
  (= (abs (slope coor1 coor2)) 1))

#|
(define cor1 (make-coor 1 6))
(define cor2 (make-coor 2 3))
(define w (list (= 1 2)(= 0 0)(= 1 9)))
(define s (list (list 1 6) (list 2 2) (list 3 7) (list 4 1) (list 5 4) (list 6 8) (list 7 6) ))
|#

(define (safe?-two-queen new-queen-coor one-queen-coor)
  (cond ((col-same? new-queen-coor one-queen-coor) #f)
         ((slope-abs=1? new-queen-coor one-queen-coor) #f)
         (else #t)))

(define (adjoin-position row k lst)
  (cons (make-coor k row) lst))
(define (safe? k one-layout)
  (let ((new-queen-coor (car one-layout))
        (other-queen-layout (cdr one-layout)))
    (accumulate (lambda (x y) (and x y))
                #t
                (map (lambda (one-queen-coor)
                       (safe?-two-queen new-queen-coor one-queen-coor))
                     other-queen-layout))))
#|
(define (test-map)
  (map (lambda (one-queen-coor)
                       (safe?-two-queen (make-coor 1 6) one-queen-coor))
                     (cdr s)))
|#
(define (queens board-size)
  (define (queen-cols k)
    (if (= k 0)
        (list empty-board)
        (filter (lambda (positions) (safe? k positions))
                (flatmap (lambda (rest-of-queens)
                           (map (lambda (new-row)
                                  (adjoin-position new-row k rest-of-queens))
                                (enumerate-interval 1 board-size)))
                         (queen-cols (- k 1))))))
  (queen-cols board-size))


;ex2.59
(define (element-of-set? x set)
  (cond ((null? set) false)
        ((equal? x (car set)) true)
        (else (element-of-set? x (cdr set)))))
(define (union-set set1 set2)
  (cond ((or (null? set1) (null? set2)) '())
        ((element-of-set? (car set1) set2)
         (union-set (cdr set1) set2))
        (else (cons (car set1) (union-set (cdr set1) set2)))))

;ex2.61
(define (adjoin-set x set)
  (cond ((null? set) (list x))
        ((= x (car set)) set)
        ((< x (car set)) (cons x set))
        (else (cons (car set) (adjoin-set x (cdr set))))))

(define (union-set-sorted set1 set2)
  (cond ((null? set1) set2)
        ((null? set2) set1)
        (else (let ((begin1 (car set1))
                    (begin2 (car set2)))
                (cond ((= begin1 begin2) (cons begin1 (union-set-sorted (cdr set1)(cdr set2))))
                      ((< begin1 begin2) (cons begin1 (union-set-sorted (cdr set1) set2)))
                      ((< begin2 begin1) (cons begin2 (union-set-sorted set1 (cdr set2)))))))))








