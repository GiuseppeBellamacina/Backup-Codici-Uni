LOC		DCB		0x35, 0x39
COPPIA	FILL		4
		
		MOV		R2, #LOC
		LDRB		R3, [R2],#1
		LSL		R3, R3, #4
		LDRB		R4, [R2]
		AND		R4, R4, #0xF
		ORR		R3, R3, R4
		MOV		R2, #COPPIA
		STRB		R3, [R2]
		
		END
