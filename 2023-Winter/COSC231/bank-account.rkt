; Things that the bank needs to be able to do
;See total amount deposited into the bank
;see total amount withdrawn
;create a new account
;View account as manager and as user
;Deposit and withdraw from people's accounts
;See total amount of cash in the bank
;Be able to apply interest to an account

; TODO:
;See total amount deposited into the bank
;see total amount withdrawn
;See total amount of cash in the bank
;Be able to apply interest to an account

; Account
(define make-account
  (lambda (acc-name init-sin init-amt int-rate init-pin)
    (let ((bal init-amt)
          (credential init-pin)
          (name acc-name)
          (rate (/ int-rate 100))
          (account (auto-increment))
          (sin init-sin)
          (tdeposit init-amt)
          (twithdraw 0))
      (lambda (msg arg)
        (case msg
          (`check-pin (if (not (eqv? arg credential))
                          (begin
                            (display "This is not the PIN for this user")
                            (newline)
                            #F)
                          (begin
                            (display "User PIN accepted")
                            (newline)
                            #T)
                          ))
          (`deposit (set! bal (+ bal arg))
                    (set! tdeposit (+ tdeposit arg)))
          (` withdraw (if (>= bal arg)
                          (begin
                            (set! bal (- bal arg))
                            (set! twithdraw (+ twithdraw arg))
                            #T)
                          (begin
                            (display "Not enough funds... ")
                            (display "You only have $")
                            (display bal)
                            (display " in your account.")
                            (newline)
                            #F
                            )))
          (`get-balance bal)
          (`get-interest rate)
          (`get-name (display name))
          (`reset-password (set! credential arg))
          (`get-info (display "Account Name: ")
                     (display name)
                     (newline)
                     (display "Account Number: ")
                     (display account)
                     (newline)
                     (display "SIN: ")
                     (display sin)
                     (newline)
                     (display "Account Balance: ")
                     (display bal)
                     (newline)
                     (display "Interest Rate: ")
                     (display rate)
                     (newline)
                     (display "Total Deposits: ")
                     (display tdeposit)
                     (newline)
                     (display "Total Withdrawals: ")
                     (display twithdraw)
                     )
          (`get-acc-num account)
          )))))

; Account number incrementer
(define auto-increment
  (let ((i 1000))
    (lambda()
      (set! i (+ 1 i))
      i
      )
    )
  )

; Bank
(define make-bank
  (lambda (b-name pwd)
    (let ((bank-name b-name)
          (manager-pin pwd)
          (accounts `())
          (tdeps 0)
          (twiths 0)
          )
      (lambda (action args pin)
        (case action
          (`make-new-acc
           (if (not (eqv? (list-size args 0) 5))
               (display "Creating a new account needs 5 arguments")
               (if (not (eqv? manager-pin pin))
                   (display "Incorrect Manager PIN")
                   (begin
                     (display "You are making a new account")
                     (set! accounts (cons (make-account
                                           (car args)
                                           (cadr args)
                                           (caddr args)
                                           (cadddr args)
                                           (cadddr (cdr args)))
                                          accounts))
                     (newline)
                     (set! tdeps (+ tdeps (caddr args)))
                     (display "Account has been created!")
                     (newline)
                     ))))
          (`get-account-info
           (if (not (eqv? (list-size args 0) 1))
               (display "Getting account info needs 1 argument")
               (if (check-pin (find-account accounts (car args)) pin manager-pin)
                   ((find-account accounts (car args)) `get-info 0)
                   (display "Incorrect PIN")
                   )))
          (`make-deposit
           (if (not (eqv? (list-size args 0) 2))
               (display "Making a deposit needs 2 arguments")
               (if (check-pin (find-account accounts (car args)) pin manager-pin)
                   (begin
                     ((find-account accounts (car args)) `deposit (cadr args))
                     (set! tdeps (+ (cadr args) tdeps))
                     (display "You have made a deposit")
                     )                                                         
                   (display "Incorrect PIN"))))
          (`make-withdrawal
           (if (not (eqv? (list-size args 0) 2))
               (display "Making a withdrawal needs 2 arguments")
               (if (check-pin (find-account accounts (car args)) pin manager-pin)
                   (begin
                     (if ((find-account accounts (car args)) `withdraw (cadr args))
                         (begin
                           (set! twiths (+ twiths (cadr args)))
                           (display "You have made a withdrawal")
                         )
                         (display "Incorrect PIN"))))))
          (`show-total-deposits
           (if (eqv? manager-pin pin)
               (begin
                 (display "Total deposits in bank: $")
                 (display tdeps)
                 (newline)
                 )
               (display "Incorrect PIN")))
          (`show-total-withdrawals
           (if (eqv? manager-pin pin)
               (begin
                 (display "Total withdrawals from bank: $")
                 (display twiths)
                 (newline)
                 )
               (display "Incorrect PIN")))
          (`show-total-cash
           (if (eqv? manager-pin pin)
               (begin
                 (display "Total cash in bank: $")
                 (display (get-total accounts 0))
                 (newline)
                 )
               (display "Incorrect PIN")))
          (`apply-interest
           (if (not (eqv? (list-size args 0) 1))
               (display "Making a withdrawal needs 1 argument")
               (if (eqv? manager-pin pin)
                   (begin
                     ((find-account accounts (car args)) `deposit (* ((find-account accounts (car args)) `get-interest 0) ((find-account accounts (car args)) `get-balance 0)))
                     (display "Interest has been added to account")
                     (newline)
                     )
                   (display "Incorrect PIN")))
          ))))))


; Helper to get total cash in bank
(define get-total
  (lambda (l acc)
    (if (null? l)
        acc
        (get-total (cdr l) (+ acc ((car l) `get-balance 0))))))

; Helper to count number of elements in list
(define list-size
  (lambda (l acc)
    (if (null? l)
        acc
        (list-size (cdr l) (+ 1 acc)))))

; Helper to find the account which matches the account number
(define find-account
  (lambda (l acc-num)
    (if (null? l)
        (begin
          (display "The account number was not found in the list of accounts")
          )
        (begin
          (if (eqv? ((car l) `get-acc-num 0) acc-num)
            (car l)
            (find-account (cdr l) acc-num)
            ))
        )
    )
  )

; Helper to determine if the correct user or manager pin is entered
(define check-pin
  (lambda (account pin manager-pin)
    (if (null? account)
        #f
        (if (eqv? pin manager-pin)
            #t
            (account `check-pin pin)
            ))))



;Test Bank
(define myBank (make-bank "Scotia" 1234))
(myBank `make-new-acc `("Joe Smith" 123456789 20 1.23 1111) 1234)
(myBank `make-new-acc `("Someone Anyone" 987654321 100 1.5 9876) 1234)