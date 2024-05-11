NUMEL		DCD		7
NUM1			DCD		2,3,4,1,5,-2,4
SOMMA		FILL		4
		
			MOV		R6, #SOMMA
			MOV		R2, #NUMEL
			LDR		R2, [R2]
			MOV		R3, #NUM1
		
CICLO		LDR		R5, [R3]
			ADD		R4, R4, R5
			ADD		R3, R3, #4
			SUB		R2 ,R2, #1
			CMP		R2, #0
			BGT		CICLO
		
			STR		R4, [R6]

			END
