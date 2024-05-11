NUMEL	DCD		10
ARR1		DCD		7, 2, 1, 3, 5, 9, -10, 8, 2, 0
ARR2		DCD		3, 1, 6, 2, 8, 7, 5, -10, 0, 4
RIS		FILL		4
		
		MOV		R2, #NUMEL
		LDR		R2, [R2]
		MOV		R3, #ARR1
		MOV		R4, #ARR2
		MOV		R5, #RIS
		
		MOV		R6, #0
		
CICLO	LDR		R7, [R3],#4
		LDR		R8, [R4],#4
		MOV		R9, #0
		CMP		R8, #0
		BGE		MULT

		MVN		R7, R7
		ADD		R7, R7, #1
		MVN		R8, R8
		ADD		R8, R8, #1

MULT		CMP		R8, #0
		BEQ		SOMMA
		SUB		R8, R8, #1
		ADD		R9, R9, R7
		B		MULT
SOMMA	ADD		R6, R6, R9
		SUBS		R2, R2, #1
		BGT		CICLO
		
FINE		STR		R6, [R5]
		
		END
