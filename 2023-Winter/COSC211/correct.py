one = 0
two = 0
three = 0
four = 64
for i in range(-2, 11):
    one = pow(i, 3)
    two = pow(i, 2) * 14
    three = i * 56
    print(i, " is " ,(one - two + three - four))

# 0 STOP
# 1 LD
# 2 STO
# 3 ADD
# 4 SUB
# 5 MPY
# 6 DIV
# 7 IN
# 8 OUT
# 9 BR
# 10 BGTE

