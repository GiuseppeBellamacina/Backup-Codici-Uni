Na		DCD		20
Nb		DCD		10
Nc		DCD		15
RESULT	FILL		4
		
		MOV		R6, #Na
		LDR		R6, [R6]
		MOV		R7, #Nb
		LDR		R7, [R7]
		MOV		R8, #Nc
		LDR		R8, [R8]
		
		MOV		R0, #18
		
		STMFD	SP!, {R6, R7, R8}
		BL		OP1
		;LDMFD	SP!, {R1,R2,R3}
		LDR		R1, [SP], #12
		
		MOV		R2, #RESULT
		STR		R1, [R2]
		
		END
		
		
OP1		STMFD	SP!, {R0, R1, R2, R12, LR}		;Salvataggio vecchi valori registri
		ADD		R12, SP, #12
		LDR		R0, [R12, #8]
		LDR		R1, [R12, #12]
		LDR		R2, [R12, #16]
		
		ADD		R0, R0, R1
		SUB		R0, R0, R2
		
		STR		R0, [R12, #8]
		LDMFD	SP!, {R0, R1, R2, R12, LR}
		
		MOV		PC, LR
		
