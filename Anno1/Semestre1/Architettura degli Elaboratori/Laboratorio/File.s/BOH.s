ARR		DCD		1, 2, 3, 4, 5, 6, 7, 32, 9, 10
DIM		DCD		10
MIN		FILL		4
MAX		FILL		4
		
		MOV		R0, #ARR
		MOV		R1, #DIM
		MOV		R4, #MIN
		MOV		R5, #MAX
		LDR		R1, [R1]
		
CICLO1	LDR		R2, [R0]
		ADD		R0, R0, #4
		LDR		R3, [R0]
		SUB		R1, R1, #1
		CMP		R1, #0
		BEQ		F1
		CMP		R2, R3
		BLE		CICLO1
		
F1		STR		R2, [R4]
		MOV		R0, #ARR
		MOV		R1, #DIM
		LDR		R1, [R1]
		
CICLO2	LDR		R2, [R0]
		ADD		R0, R0, #4
		LDR		R3, [R0]
		SUB		R1, R1, #1
		CMP		R1, #0
		BEQ		FINE
		CMP		R2, R3
		BGE		CICLO2
		
FINE		STR		R6, [R5]
