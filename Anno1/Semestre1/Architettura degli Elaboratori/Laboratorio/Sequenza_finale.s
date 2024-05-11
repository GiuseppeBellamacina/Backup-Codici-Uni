       ;Dati   due array a[] e b[], controllare se l'array a[] finisce con la stessa sequenza dell'array b[] (supporre a[] sempre piu' lungo di b[])
ARR_A  DCD     1,5,6,9,8,2,4,5,3,0
DIM_A  DCD     10
ARR_B  DCD     5,3,0
DIM_B  DCD     3
RES    FILL    4

       ;R0:    iteratore ARR_A a partire dall'indice DIM_A - DIM_B
       ;R1:    dimensione ARR_A
       ;R2:    iteratore ARR_B
       ;R3:    dimensione ARR_B
       ;R4:    el ARR_A
       ;R5:    el ARR_B
       ;R6:    DIM_A - DIM_B
       ;R12:   1 se va bene, altrimenti

       MOV     R0, #ARR_A
       MOV     R1, #DIM_A
       LDR     R1, [R1]
       MOV     R2, #ARR_B
       MOV     R3, #DIM_B
       LDR     R3, [R3]
       MOV     R12, #1
       SUB     R6, R1, R3

IT     ADD     R0, R0, #4
       SUB     R6, R6, #1
       CMP     R6, #0
       BGT     IT

CICLO  SUB     R3, R3, #1
       CMP     R3, #-1
       BEQ     FINE
       LDR     R4, [R0], #4
       LDR     R5, [R2], #4
       CMP     R4, R5
       BEQ     CICLO

       MOV     R12, #0

FINE   MOV     R0, #RES
       STR     R12, [R0]
       END