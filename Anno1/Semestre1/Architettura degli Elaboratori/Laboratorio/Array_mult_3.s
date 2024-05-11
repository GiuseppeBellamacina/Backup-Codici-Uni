ARR    DCD     5,1,9,3,4,12,14,22,6,8
NUMEL  DCD     10
RES    FILL    40

       ;R0:    contiene il numero di elementi di ARR
       ;R1:    contiene progressivamente il puntatore agli elementi di ARR
       ;R2:    contiene progressivamente gli elementi di ARR
       ;R3:    contiene una copia del numero inizialmente conservato in R2 all'inizio del CHECK
       ;R4:    contiene l'indirizzo dell'array da restituire

       MOV     R0, #NUMEL
       LDR     R0, [R0]
       MOV     R1, #ARR
       MOV     R4, #RES

CICLO  LDR     R2, [R1]
       LDR     R3, [R1], #4
       SUB     R0, R0, #1
       CMP     R0, #0
       BEQ     FINE

CHECK  SUB     R2, R2, #3
       CMP     R2, #3
       BGE     CHECK
       CMP     R2, #0
       BEQ     PUT
       B       CICLO

PUT    STR     R3, [R4], #4
       B       CICLO

FINE   END