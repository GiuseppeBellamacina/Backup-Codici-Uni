       ;dato   un array a[] costruire un array b[] tale che b[i] = a[i] * a[i+1]
ARR_A  DCD     5,6,7,9,10
DIM_A  DCD     5
ARR_B  FILL    16

       ;R0:    iteratore di ARR_A
       ;R1:    dimensione di ARR_A
       ;R2:    iteratore di ARR_B
       ;R3:    a[i]
       ;R4:    a[i+1]
       ;R5:    prodotto[i]

       MOV     R0, #ARR_A
       MOV     R1, #DIM_A
       LDR     R1, [R1]
       MOV     R2, #ARR_B
       MOV     R5, #0

CICLO  LDR     R3, [R0]
       LDR     R4, [R0, #4]

MULT   ADD     R5, R5, R3
       SUB     R4, R4, #1
       CMP     R4, #0
       BGT     MULT

       STR     R5, [R2], #4
       MOV     R5, #0
       ADD     R0, R0, #4
       SUB     R1, R1, #1
       CMP     R1, #1 ;si fanno n-1 iterazioni
       BEQ     FINE
       B       CICLO

FINE   END