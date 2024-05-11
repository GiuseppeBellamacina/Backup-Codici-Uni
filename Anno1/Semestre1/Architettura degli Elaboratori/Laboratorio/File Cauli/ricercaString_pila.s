TSTRING	DCB		0x41, 0x41, 0x41, 0x41, 0x42, 0x43, 0x43, 0x43, 0x43
PSTRING	DCB		0x41, 0x42, 0x43
TNUMEL	DCD		9
PNUMEL	DCD		3
RESULT	FILL		4
		
		MOV		R0, #TSTRING
		MOV		R1, #PSTRING
		MOV		R4, #RESULT
		
		MOV		R2, #TNUMEL
		LDR		R2, [R2]
		MOV		R3, #PNUMEL
		LDR		R3, [R3]
		SUB		R2, R2, R3
		ADD		R2, R2, R0
		ADD		R3, R3, R1
		
		STMFD	SP!, {R0, R1, R2, R3}
		BL		RICERCA
		LDMFD	SP!, {R0, R1, R2, R3}
		
		STR		R0, [R4]
		END
		
		;sottoprogramma	Ricerca stringa
RICERCA	STMFD	SP!, {R0, R1, R2, R3, R4, R12, LR}
		ADD		R12, SP, #20
		LDR		R0, [R12, #8]
		LDR		R1, [R12, #12]
		LDR		R4, [R12, #16]
		LDR		R5, [R12, #20]
		
CICLOR	MOV		R2, R0
		MOV		R3, R1
		STMFD	SP!, {R2, R3, R5}
		BL		CMPSTR
		
		LDMFD	SP!, {R2, R3, R5}
		CMP		R2, #0
		BGT		FATTOR
		
		ADD		R0, R0, #1
		CMP		R4, R0
		BGE		CICLOR
		
		MOV		R0, #-1
FATTOR	STR		R0, [R12, #8]
		LDMFD	SP!, {R0, R1, R2, R3, R4, R12, LR}
		MOV		PC, LR
		
		
		
		;sottoprogramma	Confronto stringhe
CMPSTR	STMFD	SP!, {R0, R1, R2, R3, R4, R5, R12}
		ADD		R12, SP, #24
		LDMED	R12, {R0, R1, R2}
		MOV		R5, #0
		
CICLOCS	LDRB		R3, [R0],#1
		LDRB		R4, [R1],#1
		CMP		R3, R4
		BNE		FINECS
		CMP		R2, R1
		BGT		CICLOCS
		
		MOV		R5, #1
FINECS	STR		R5, [R12, #4]
		LDMFD	SP!, {R0, R1, R2, R3, R4, R5, R12}
		MOV		PC, LR
