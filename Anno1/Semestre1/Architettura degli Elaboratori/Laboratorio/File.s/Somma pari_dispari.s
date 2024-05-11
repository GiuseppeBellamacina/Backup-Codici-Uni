		;somma	degli el pari o dispari
SIZE		DCD		7
ARRAY	DCD		1,3,10,2,7,9,20
		;
		;R0		DIMENSIONE
		;R1		PTR ARRAY
		;R2		SOMMA PARI/DISP
		;R3		MASCHERA PER AND PARI (0), O DISPARI (1)
		;R5		EL ARRAY
		;R6		CONTATORE
		;
		MOV		R2, #0
		MOV		R6, #0
		
		MOV		R0, #SIZE
		LDR		R0, [R0]
		
		MOV		R1, #ARRAY
LOOP
		CMP		R0, #0
		BEQ		END_LOOP
		
		LDR		R5, [R1]
		
		AND		R3, R5, #0 ;se metto 0 somma i dispari, se metto 1 somma i pari
		CMP		R3, #0 ;se l'ultimo bit è 0, il numero è zero, quindi si è fatto un and con un pari
		BNE		SKIP
		
		ADD		R2, R2, R5
		ADD		R6, R6, #1
		
		
SKIP
		SUB		R0, R0, #1
		ADD		R1, R1, #4
		B		LOOP
END_LOOP
		END
