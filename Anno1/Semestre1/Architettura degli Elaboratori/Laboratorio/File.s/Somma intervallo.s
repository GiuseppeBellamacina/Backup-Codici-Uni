		;somma	degli el compresi tra a e b
SIZE		DCD		7
ARRAY	DCD		1,3,10,2,7,9,20
		;
		;R0		DIMENSIONE
		;R1		PTR ARRAY
		;R2		SOMMA
		;R3,R4	ESTREMI INTERVALLO
		;R6		CONTATORE
		;
		MOV		R2, #0
		MOV		R6, #0
		MOV		R3, #7
		MOV		R4, #10
				
		MOV		R0, #SIZE
		LDR		R0, [R0]
		
		MOV		R1, #ARRAY
LOOP
		CMP		R0, #0
		BEQ		END_LOOP
		
		LDR		R5, [R1]
		CMP		R5, R3
		BLT		SKIP
		CMP		R5, R4
		BGT		SKIP
		
		ADD		R2, R2, R5
		ADD		R6, R6, #1
		
		
SKIP
		SUB		R0, R0, #1
		ADD		R1, R1, #4
		B		LOOP
END_LOOP
		END
