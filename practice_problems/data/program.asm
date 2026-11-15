; sums the numbers 1..10 into r1
        CONST r1, 0        ; sum
        CONST r2, 10       ; counter
        CONST r3, 1

loop:   ADD r1, r1, r2
        ; this line is only a comment
        SUB r2, r2, r3
        HALT
