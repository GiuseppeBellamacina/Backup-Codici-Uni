		;STRINGA	DCB		0X39, 0X35 ;little endian, quindi a sinistra c'è il numero col 5 e a destra col 9
		;DCB		è come DCD ma inserisce singoli byte
STRINGA	DCD		0X3539
COPPIA	FILL		4
		
		MOV		R2, #STRINGA
		
		MOV		R1, #0XAA
		LSL		R1, R1, #16 ;shift logico a sinistra
		LDRB		R1, [R2]
		STRB		R1, [R2, #1]

		END