(define foo
  (let ((n 0))
    (lambda ()
      (begin
        (set! n (+ n 1))
        n
        ))))