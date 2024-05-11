TSTRING	DCB		0x41, 0x41, 0x41, 0x41, 0x41, 0x43, 0x43, 0x43, 0x43
PSTRING	DCB		0x41, 0x42, 0x43
NUMELT	DCD		9
NUMELP	DCD		3
		
RESULT	FILL		4
		
		MOV		R0, #TSTRING
		MOV		R1, #PSTRING
		
		MOV		R2, #NUMELT
		LDR		R2, [R2]
		MOV		R3, #NUMELP
		LDR		R3, [R3]
		
		SUB		R2, R2, R3
		ADD		R4, R0, R2
		
		ADD		R5, R1, R3
		
		STMFD	SP!, {R0, R1, R4, R5}
		BL		FINDSTR
		LDR		R0, [SP],    #16
		
		MOV		R1, #RESULT
		STR		R0, [R1]
		
		END
		
		;		Sottoprogramma Ricerca Sottostringa
		;		R0 -> indirizzo inizio Tstring
		;		R1 -> indirizzo inizio Pstring
		;		R2 -> indirizzo fine Tstring (R0 + (dimT-dimP))
		;		R3 -> indirizzo fine Pstring
FINDSTR	STMFD	SP!, {R0, R1, R2, R3, R4, R12, LR}
		ADD		R12, SP, #20
		LDR		R0, [R12, #8]
		LDR		R1, [R12, #12]
		LDR		R2, [R12, #16]
		LDR		R3, [R12, #20]
		
CICLOF	CMP		R0, R2
		BEQ		NOTFOUND
		STMFD	SP!, {R0, R1, R3}
		BL		CMPSTR
		LDR		R4, [SP], #12
		CMP		R4, #0
		BNE		FINEF
		ADD		R0, R0, #1
		B		CICLOF
		
NOTFOUND	MOV		R0, #-1
FINEF	STR		R0, [R12, #8]
		LDMFD	SP!, {R0, R1, R2, R3, R4, R12, LR}
		
		MOV		PC, LR
		
		
		;		Sottoprogramma string compare
		;		R0 -> indirizzo inizio stringa 1
		;		R1 -> indirizzo inizio stringa 2
		;		R2    -> indirizzo fine stringa 2
CMPSTR	STMFD	SP!, {R0, R1, R2, R3, R4, R5, R12}
		ADD		R12, SP, #24
		LDR		R0, [R12, #4]
		LDR		R1, [R12, #8]
		LDR		R2, [R12, #12]
		
		MOV		R3, #0
		
CICLOCMP	CMP		R1, R2
		BEQ		UGUALI
		LDRB		R4, [R0], #1
		LDRB		R5, [R1], #1
		CMP		R4, R5
		BNE		FINECMP
		B		CICLOCMP
		
UGUALI	MOV		R3, #1
FINECMP	STR		R3, [R12, #4]
		LDMFD	SP!, {R0, R1, R2, R3, R4, R5, R12}
		
		MOV		PC, LR
