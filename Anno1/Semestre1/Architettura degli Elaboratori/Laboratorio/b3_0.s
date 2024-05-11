       ;dato   un array a[] calcolare la somma degli elementi che hanno il b3 pari a "0"
ARR    DCD     10, 8, 4, 95, 22
DIM    DCD     5
RES    FILL    4

       ;R0:    iteratore di ARR
       ;R1:    dimensione di ARR
       ;R2:    contiene progressivamente gli elementi di ARR
       ;R3:    contiene il valore del b3
       ;R4:    somma finale

       MOV     R0, #ARR
       MOV     R1, #DIM
       LDR     R1, [R1]
       MOV     R4, #0

CICLO  LDR     R2, [R0], #4
       AND     R3, R2, #8
       CMP     R3, #0
       BEQ     SOMMA
       B       SUBT

SOMMA  ADD     R4, R4, R2

SUBT   SUB     R1, R1, #1
       CMP     R1, #0
       BEQ     FINE
       B       CICLO

FINE   MOV     R0, #RES
       STR     R4, [R0]
       END