ARR1		DCD		33, -45, 99, 1, 0, -4, 76, -3, 5, 11
NUMEL	DCD		10
RIS		FILL		4
		
		MOV		R0, #NUMEL ;IMPOSTA su r0 il valore dell'indirizzo di numel
		LDR		R0, [R0] ;prende l'indirizzo di numel presente in r0 e CARICA in r0
					    ;il contenuto dell'indirizzo già specificato
		MOV		R1, #ARR1 ;IMPOSTA r1 sul valore dell'indirizzo del primo elemento di arr1
		MOV		R2, #0 ;IMPOSTA r2 a 0
		
CICLO	LDR		R3, [R1] ;CARICA su r3 ciò che c'è all'indirizzo presente in r1
		ADD		R2, R2, R3 ;SOMMA i contenuti di r2 e r3 e li salva in r2
		SUB		R0, R0, #1 ;DETRAE 1 dal contenuto di r0
		ADD		R1, R1, #4 ;SOMMA 4 al contenuto di r1
		CMP		R0, #0 ;CONTROLLA se r0 è uguale a 0 (condizione fine ciclo)
		BGT		CICLO ;ultima istruzione che chiude il ciclo
		
		MOV		R4, #RIS ;IMPOSTA r4 con l'indirizzo di ris
		STR		R2, [R4] ;CONSERVA sulla locazione con indirizzo presente in r4 il valore di r2
		
		END				;abbiamo finito
