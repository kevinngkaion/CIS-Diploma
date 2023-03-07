(define code-l `((a b) (b c) (c a)))

(define make-encoder
  (lambda (code arg)
    (let ((codes code))
      (if (eqv? arg `decode)
          (set! codes deep-rev)
          (display "Else")
          )
      (lambda (msg-l)
        (letrec ((encode (lambda (msg-l acc)
                           (if (null? msg-l)
                               acc
                               (encode (cdr msg-l) (append acc (cdr (assq (car msg-l) codes)) ))
                               )
                           )
                         ))
          (encode msg-l `())
          )
        )
      )
    )
  )
; TODO: Need to make deep-rev procedure
(define deep-rev `((b a) (c b) (a c)))

(define encoder-1 (make-encoder code-l `encode))
(encoder-1 '(a b a c a b))
(define decoder-1 (make-encoder code-l `decode))
(decoder-1 `(b c b a b c))

