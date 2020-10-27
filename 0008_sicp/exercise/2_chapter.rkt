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