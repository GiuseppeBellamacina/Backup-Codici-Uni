STRINGA	DCD		0X3539
COPPIA	FILL		4
		
		MOV		R2, #STRINGA
		LDRB		R0, [R2, #1]
		LSL		R0, R0, #4
		LDRB		R1, [R2]

		AND 		R1, R1, 0xF
		ORR		R0, R0, R1

		MOV		R3, #COPPIA
		STRB		R0, [R3]
		
		END
