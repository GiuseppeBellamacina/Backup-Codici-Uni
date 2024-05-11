NUMEL	DCD		5
NUM1		DCD		2,3,4,1,5
RESULT	FILL		4
		
		MOV		R0, #NUMEL
		LDR		R0, [R0]
		MOV		R1, #NUM1
		
		STMFD	SP!, {R0, R1}
		BL		SOMMA
		LDMFD	SP!, {R0, R1}
		MOV		R2, #RESULT
		STR		R0, [R2]
		
		END
		
		
		;sottoprogramma	somma
SOMMA	STMFD	SP!, {R0, R1, R2, R3, R12}
		ADD		R12, SP, #16
		LDMED	R12, {R0, R1}
		;LDR		R0, [R12, #4]
		;LDR		R1, [R12, #8]
		MOV		R3, #0
		
CICLO	LDR		R2, [R1],#4
		ADD		R3, R3, R2
		SUBS		R0 ,R0, #1
		BGT		CICLO
		
		STR		R3, [R12, #4]
		LDMFD	SP!, {R0, R1, R2, R3, R12}
		MOV		PC, LR
		;BX		LR
