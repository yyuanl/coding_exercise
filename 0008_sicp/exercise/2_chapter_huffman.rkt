#lang sicp
#|
huffman编码
|#
(define (append list1 list2)
  (if (null? list1)
      list2
      (cons (car list1) (append (cdr list1) list2))))
; 树叶的表示
(define (make-leaf symbol weight)
  (list 'leaf symbol weight))
(define (leaf? object)
  (eq? (car object) 'leaf))
(define (symbol-leaf x) (cadr x))
(define (weight-leaf x) (caddr x))

;归并两个结点做出一颗树
(define (make-code-tree left right)
  (list left
        right
        (append (symbols left) (symbols right))
        (+ (weight left) (weight right))))

(define (left-branch tree) (car tree))  ;左子树
(define (right-branch tree) (cadr tree)) ; 右子树
(define (symbols tree)  ;树（结点）的符号集
  (if (leaf? tree)
      (list (symbol-leaf tree))
      (caddr tree)))
(define (weight tree)  ;树（结点）权重
  (if (leaf? tree)
      (weight-leaf tree)
      (cadddr tree)))

;解码
(define (decode bits tree)
  (define (decode-1 bits current-branch)
    (if (null? bits)
        '()
        (let ((next-branch (choose-branch (car bits) current-branch)))
          (if (leaf? next-branch)
              (cons (symbol-leaf next-branch)
                    (decode-1 (cdr bits) tree))
              (decode-1 (cdr bits) next-branch)))))
  (decode-1 bits tree))
(define (choose-branch bit branch)
  (cond ((= bit 0) (left-branch branch))
        ((= bit 1) (right-branch branch))
        (else (error "bad bit -- CHOOSE-BRANCH" bit))))

;ex2.67
(define sample-tree
  (make-code-tree (make-leaf 'A 4)
                  (make-code-tree
                   (make-leaf 'B 2)
                   (make-code-tree (make-leaf 'D 1)
                                   (make-leaf 'C 1)))))
(define sample-message '(0 1 1 0 0 1 0 1 0 1 1 1 0))
;ex2.68
(define (encode message tree)
  (if (null? message)
      '()
      (append (encode-symbol (car message) tree)
              (encode (cdr message) tree))))
(define (encode-symbol sym tree)
  (define (encode-symbol s current-tree result)
    (if (leaf? current-tree)
        result
        (cond ((symbol-in-branch s (left-branch current-tree)) (encode-symbol s (left-branch current-tree) (append result (list '0))))
              ((symbol-in-branch s (right-branch current-tree)) (encode-symbol s (right-branch current-tree) (append result (list '1))))
              (else (error "there is no symbol")))))
  (encode-symbol sym tree '()))

(define (symbol-in-branch s tree)
  (symbol-in-sets s (symbols tree)))
(define (symbol-in-sets s sets)
  (cond ((null? sets) #f)
        ((eq? s (car sets)) #t)
        (else (symbol-in-sets s (cdr sets)))))






