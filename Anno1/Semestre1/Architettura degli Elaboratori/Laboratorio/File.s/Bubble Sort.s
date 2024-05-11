Size		DCD		10
Array	DCD		3,5,4,2,9,0,7,6,1,8
		
		;R0:		Size
		;R1:		Ptr Array
		;R2:		Flag
		;R3:		Elemento corrente
		;R4:		Elemento successivo
		
Restart
		MOV		R2, #0 ;imposta il flag a 0
		MOV		R0, #Size
		LDR		R0, [R0]
		MOV		R1, #Array
Loop
		CMP		R0, #1 ;si mette 1 anzichè 0 perchè si fanno n-1 controlli tra un el e l'altro, non n
		BEQ		End_Loop
		LDR		R3, [R1] ;carico elemento corrente
		LDR		R4, [R1, #4] ;carico elemento successivo
		CMP		R3, R4 ;confronto questi ultimi
		BLE		No_Swap ;se il primo è <= del secondo, va bene e non effettuo lo swap
		;se		non si usa la branch, allora si effettua lo swap
		STR		R4, [R1] ;conservo l'elemento successivo al posto dell'elemento corrente con str
		STR		R3, [R1, #4] ;conservo l'elemento corrente al posto dell'elemento successivo con str
		MOV		R2, #1 ;quando si effettua uno swap si attiva il flag impostandolo a 1
		
No_Swap
		ADD		R1, R1, #4 ;punto al prossimo elemento
		SUB		R0, R0, #1 ;tolgo un'iterazone NB: si effettuano n-1 iterazioni ogni ciclo
		B		Loop
End_Loop
		CMP		R2, #1 ;verifica se ci sono stati degli swap giunti alla fine dell'array
		BEQ		Restart ;se c'è stato qualche swap, l'array potrebbe non essere ancora ordinato, quindi si ricomincia
		END
