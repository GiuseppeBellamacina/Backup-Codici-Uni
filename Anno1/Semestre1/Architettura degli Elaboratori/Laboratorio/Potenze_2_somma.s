POT    DCD     5
RES    FILL    4

       MOV     R1, #1
       MOV     R2, #POT
       LDR     R2, [R2]

CICLO  CMP     R2, #0
       BEQ     FINE
       ADD     R1, R1, R1
       SUB     R2, R2, #1
       B       CICLO

FINE   
       MOV     R0, #RES
       STR     R1, [R0]
       END