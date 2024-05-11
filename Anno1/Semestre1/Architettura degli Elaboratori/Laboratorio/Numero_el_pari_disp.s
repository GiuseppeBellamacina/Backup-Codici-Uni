       ;dato   un array "a" determinare se il numero di elementi maggiori di 10 e' un numero pari o dispari
ARR    DCD     1,3,11,58,64,9,10,85,118,45,18
NUMEL  DCD     11
RES    FILL    4

       ;R0:    numero elementi di ARR
       ;R1:    iteratore di ARR
       ;R2:    contiene progressivamente i vari elementi di ARR
       ;R3:    contiene un counter degli elementi maggiori di 10 e alla fine
       ;       conterra' 0 se sono in numero pari, o 1 se sono in numero dispari

       MOV     R0, #NUMEL
       LDR     R0, [R0]
       MOV     R1, #ARR
       MOV     R3, #0

CICLO  LDR     R2, [R1], #4
       CMP     R2, #10
       BGT     INC

SUBT   SUB     R0, R0, #1
       CMP     R0, #0
       BEQ     FINE
       B       CICLO

INC    ADD     R3, R3, #1
       B       SUBT

FINE   AND     R3, R3, #1
       MOV     R0, #RES
       STR     R3, [R0]
       END