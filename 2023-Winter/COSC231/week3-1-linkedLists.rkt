(define a
  (cons 4 3))
(define b
  (cons 4 3))

(define l
  '(a b c (d e) (f g) h))

(define count
  (lambda (ls)
    (if (null? ls)
        0
        (+ 1 (count (cdr ls))))))

(define dcount
  (lambda (ls)
    (if (null? ls)
        0
        (if (pair? (car ls))
            (+ (dcount (car ls)) (dcount(cdr ls)))
            (+ 1 (dcount (cdr ls)))))))