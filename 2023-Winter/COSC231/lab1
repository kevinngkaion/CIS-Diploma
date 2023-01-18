(define add1
  (lambda (n)
    (+ n 1)))

(define sub1
  (lambda (n)
    (- n 1)))

(define add
  (lambda (a b)
    (if (= b 0)
        a
        (add (add1 a) (sub1 b)))))

(define mult
  (lambda (a b)
    (if (= b 0)
        0
        (if (= b 1)
            a
            (+ a (mult a (- b 1)))))))

(define power
  (lambda (a b)
    (if (= b 0)
        1
        (if (= b 1)
            a
            (* a (power a (- b 1)))))))

(define power2
  (lambda (a b)
    (if (= b 0)
        1
        (if (= b 1)
            a
            (if (= (modulo b 2) 1)
                (* a (power2 a (/ (- b 1) 2)) (power2 a (/ (- b 1) 2)))
                (* (power2 a (/ b 2)) (power2 a (/ b 2))))))))