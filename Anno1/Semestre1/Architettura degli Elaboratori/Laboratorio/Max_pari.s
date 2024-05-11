        ;massimopari di un array
ARR     DCD     1,2,5,8,9,12,64,33,-318,10
DIM     DCD     10
RES     FILL    4

        ;R0:    iteratore ARR
        ;R1:    dimensione ARR
        ;R2:    contiene progressivamente gli elementi di ARR
        ;R3:    bit-tester
        ;R4:    massimo

        MOV     R0, #ARR
        MOV     R1, #DIM
        LDR     R1, [R1]

CICLO   SUB     R1, R1, #1
        CMP     R1, #-1
        BEQ     FINE
        LDR     R2, [R0], #4
        AND     R3, R2, #1
        CMP     R3, #0
        BEQ     CALCMAX
        B       CICLO

CALCMAX CMP     R2, R4
        BGT     MAX
        B       NO_MAX
MAX     MOV     R4, R2
NO_MAX  B       CICLO

FINE    MOV     R0, #RES
        STR     R4, [R0]
        END