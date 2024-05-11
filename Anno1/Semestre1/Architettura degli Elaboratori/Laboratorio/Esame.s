ARR_A   DCD     10, 133, 25, 89, 128
DIM_A   DCD     5
ARR_B   FILL    20

        ;R0:    iteratore di ARR_A
        ;R1:    dimensione ARR_A
        ;R2:    iteratore ARR_B
        ;R3:    filtro bit7
        ;R4:    contiene progressivamente gli elementi di ARR_A
        ;R5:    copia di R4

        MOV     R0, #ARR_A
        MOV     R1, #DIM_A
        LDR     R1, [R1]
        MOV     R2, #ARR_B
        MOV     R3, #0b10000000

CICLO   LDR     R4, [R0]
        LDR     R5, [R0], #4

TEST    AND     R4, R4, R3
        CMP     R4, R3
        BEQ     TROVATO
        B       SUCC

TROVATO STR     R5, [R2], #4
        B       SUCC

SUCC    SUB     R1, R1, #1
        CMP     R1, #0
        BEQ     FINE
        B       CICLO

FINE    END
