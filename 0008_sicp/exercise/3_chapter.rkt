#lang sicp
;ex3.1
(define (make-accumulator init)
  (let ((start init))
    (lambda (x)
      (begin (set! start (+ start x))
             start))))

;ex3.2
(define (square x) (* x x))
(define (make-monitored f)
  (let ((counter 0))
    (lambda (x)
      (cond ((eq? x 'how-many-calls?) counter)
            ((eq? x 'reset-count) (set! counter 0))
            (else (begin (set! counter (+ 1 counter)) (f x)))))))
(define s (make-monitored square))
