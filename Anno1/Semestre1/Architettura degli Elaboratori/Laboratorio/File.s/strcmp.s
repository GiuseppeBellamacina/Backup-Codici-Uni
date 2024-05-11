				;strcmp
S1				DCB		'h', 'e', 'l', 'l', 'o', 0x0
S2				DCB		'h', 'e', 'l', 'l', 'a', 0x0
				
				;R1		= S1
				;R2		= S2
				;R3		= *S1
				;R4		= *S2
				
				MOV		R1, #S1
				MOV		R2, #S2
				
Strcmp_Loop
				
				LDRB		R3, [R1]
				LDRB		R4, [R2]
				
				SUB		R0, R3, R4
				CMP		R3, R4
				BNE		End_Strcmp_Loop
				
				CMP		R3, #0
				BNE		Strcmp_Continue
				CMP		R4, #0
				BNE		Strcmp_Continue
				;R3		== 0 && R4 == 0
				MOV		R0, #0
				B		End_Strcmp_Loop
				
Strcmp_Continue
				
				ADD		R1, R1, #1
				ADD		R2, R2, #1
				B		Strcmp_Loop
				
End_Strcmp_Loop
				
				END		;su R0 va 0 se le stringhe sono uguali
				;ci		va un numero maggiore di 0 se S1 viene dopo S2
				;ci		va un numero minore di 0 se S1 viene prima di S2
