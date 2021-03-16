#lang sicp
;excercise 1.16
(define (m_fast_exp b n) ;求b的n次方
   (m_exp_iter b n 1)
)

(define (m_exp_iter b n a); 递归定义  迭代的计算过程
   (cond ((= n 0) a)
         ((even? n) (m_exp_iter (* b b) (/ n 2) a))
         (else (m_exp_iter b (- n 1) (* b a)))
    )
  )
(define (even? x)
  ( = (remainder x 2) 0 )
  )

;exercise 1.17
(define (double x)
  (+ x x)
 )
(define (halve x)
  (/ x 2)
 )
(define (multi a b)
  (cond ( (= b 0) 0 )
  ( (even? b) (double (multi a (halve b))))
        ( else (+ a (multi a (- b 1))))
   )
 )
;ex 1.18
(define (log_multi x y)
  (log_multi_iter x y 0))
(define (log_multi_iter a b temp)  ;加a  加b次
  (cond ( (= b 0) temp )
        ( (even? b) (log_multi_iter (double a ) (halve b) temp))
        ( else (log_multi_iter a ( - b 1) (+ a temp)))
  )
  )

;ex 1.29
(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))
   ))
(define (cube x)
  (* x x x))
(define (my_integral f a b n)
  (define h (/ (- a b) n))
  (define (addone x) (+ x 1))
  (define (my_term x) (* (f (+ a (* x h)))
                         (cond ( (or (= x 0) (= x n)) 1)
                               ((even? x) 4)
                               (else 2))))
  (* (/ h 3.0) (sum my_term 0 addone n)))

;ex 1.30
(define (sum_iter term a next b)
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a) (+ (term a) result))))
  (iter a 0))

(define (test f a b)
  (define (next x) (+ x 1))
  (sum_iter f a next b))
;ex 1.31
(define (product term a next b)  ; 递归计算版本
  (if (> a b)
      1
      (* (term a) (product term (next a) next b))))
(define (product_iter term a next b) ; 迭代计算版本
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a) (* (term a) result))))
  (iter a 1))
;测试
(define (test_131)
  (define (next_131 x)
    (+ x 1))
  (product cube 1 next_131 3))
(define (test_131_1)
  (define (next_131 x)
    (+ x 1))
  (product_iter cube 1 next_131 3))
;ex 1.32  函数累计的更高抽象
(define (accumulate combiner null_value term a next b)    ;递归计算
  (if (> a b)
      null_value
      (combiner (term a) (accumulate combiner null_value term (next a) next b))))

(define (accumulate_iter combiner null_value term a next b)    ;迭代计算
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a) (combiner (term a) result))))
  (iter a null_value))

(define (new_sum term a next b)
  (accumulate_iter + 0 term a next b))
(define (new_product term a next b)
  (accumulate * 1 term a next b))

(define (test_132)
  (define (add1 x)
    (+ x 1))
  (new_sum cube 1 add1 3))






