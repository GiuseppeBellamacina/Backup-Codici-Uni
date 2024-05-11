ARR1		DCD		2, 0, 7, 18
NUM		DCD		4
RIS		FILL		4
		
		
		
SOMMA	STMFD	SP!, {R0, R1, R2, R3} ;Equivalente a dire STR R0, [SP], #4 ; STR R1, [SP], #4 ;STR R2, [SP], #4 ; STR R3, [SP], #4
		LDR		R0, [SP, #16]
		LDR		R1, [SP, #20]
		
		MOV		R2, #0
		
CICLOS	LDR		R2, [R0], #4
		ADD		R3, R3, R2
		SUB		R1, R1, #1
		CMP		R1, #0
		BGT		CICLOS
		
		STR		R3, [SP, #16]
		LDMFD	SP!, {R0, R1, R2, R3}
		MOV		PC, LR
