NUMEL	DCD		10
ARR1		DCD		7, 2, 1, 3, 5, 9, -10, 8, 2, 0
ARR2		DCD		3, 1, 6, 2, 8, 7, 5, -10, 0, 4
RIS		FILL		4
		
		MOV		R2, #NUMEL
		LDR		R2, [R2]
		MOV		R0, #ARR1
		MOV		R1, #ARR2
		
		STMFD	SP!, {R0, R1, R2}
		BL		PROD
		LDMFD	SP!, {R0, R1, R2}
		
		MOV		R1, #RIS
		STR		R0, [R1]
		END
		
		
		;sottoprogramma	prodotto scalare
PROD		STMFD	SP!, {R0, R1, R2, R3, R4, R5, R12, LR}
		ADD		R12, SP, #24
		LDR		R0, [R12, #8]
		LDR		R1, [R12, #12]
		LDR		R2, [R12, #16]
		MOV		R5, #0
		
CICLOP	LDR		R3, [R0],#4
		LDR		R4, [R1],#4
		
MULTCALL	STMFD	SP!, {R3, R4}
		BL		MULT
		LDMFD	SP!, {R3, R4}
		ADD		R5, R5, R3
		SUBS		R2, R2, #1
		BGT		CICLOP
		
		STR		R5, [R12, #8]
		LDMFD	SP!, {R0, R1, R2, R3, R4, R5, R12, LR}
		MOV		PC, LR
		
		
		;sottoprogramma	moltiplicazione
MULT		STMFD	SP!, {R0, R1, R2, R12}
		ADD		R12, SP, #12
		LDMED	R12, {R0, R1}
		MOV		R2, #0
		
		CMP		R1, #0
		BGE		CICLOM
		MVN		R0, R0
		ADD		R0, R0, #1
		MVN		R1, R1
		ADD		R1, R1, #1
		
CICLOM	CMP		R1, #0
		BEQ		ENDMULT
		SUB		R1, R1, #1
		ADD		R2, R2, R0
		B		CICLOM
		
ENDMULT	STR		R2, [R12, #4]
		LDMFD	SP!, {R0, R1, R2, R12}
		MOV		PC, LR
