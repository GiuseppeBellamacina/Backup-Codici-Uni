        ;Dato   un vettore a[], costruire un vettore b[] che abbia solo
        ;gli    elementi di a divisibili per una costante fornita su R0

ARR_A   DCD     10,4,25,55,87,12
DIM_A   DCD     6
ARR_B   FILL    24

        ;R0:    divisore
        ;R1:    iteratore ARR_A
        ;R2:    dimensione ARR_A
        ;R3:    iteratore ARR_B
        ;R4:    contiene progressivamente gli elementi di ARR_A
        ;R5:    copia di R4

        MOV     R0, #3
        MOV     R1, #ARR_A
        MOV     R2, #DIM_A
        LDR     R2, [R2]
        MOV     R3, #ARR_B

CICLO   LDR     R5, [R1]
        LDR     R4, [R1], #4

DIV     SUB     R4, R4, R0
        CMP     R4, #0
        BEQ     TROVATO
        BLT     SUCC
        B       DIV

SUCC    SUB     R2, R2, #1
        CMP     R2, #0
        BEQ     FINE
        B       CICLO

TROVATO STR     R5, [R3], #4
        B       SUCC

FINE    END