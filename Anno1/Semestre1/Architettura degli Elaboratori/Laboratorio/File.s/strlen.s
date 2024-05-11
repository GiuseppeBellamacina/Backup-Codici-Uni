				;strlen
String			DCB		'h', 'e', 'l', 'l', 'o', 0x0 ;0 è il carattere null terminator (\0)
				
				;R0		= counter
				;R1		= ptr
				;R2		= i-th character
				
				MOV		R1, #String
				MOV		R0, #0
				
Strlen_Loop
				
				LDRB		R2, [R1] ;mette su R2 solo il primo byte
				CMP		R2, #0
				BEQ		End_Strlen_Loop
				ADD		R1, R1, #1 ;punto al byte successivo (non alla parola successiva)
				ADD		R0, R0, #1
				B		Strlen_Loop
				
End_Strlen_Loop
				
				END