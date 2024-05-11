ARR1		DCD		22, -1, -33, 9 ;riempio l'array
NUMEL	DCD		4 ;dimensione array
RESULT	FILL		8 ;lascio 2 parole di memoria vuote
		            ;(basterebbe	4 anzichè 8 se non conservo pure R3 alla fine)
		
		MOV		R0, #ARR1 ;copio su R0 l'indirizzo del primo el dell'array
		MOV		R1, #NUMEL ;copio su R1 l'indirizzo della dim dell'array
		LDR		R1, [R1] ;carico su R1 la dim dell'array
		STMFD	SP!, {R0, R1} ;conservo sullo stack R0 e R1 e aggiorno SP
		BL		CALCMIN ;avvio il sottoprogramma
		LDMFD	SP!, {R2, R3} ;riprendo dallo stack i valori che hanno assunto R2 e R3 alla fine del sottoprogramma
		MOV		R0, #RESULT ;copio su R0 l'indirizzo dell'area di memoria riservata su cui salvare i dati
		STR		R2, [R0] ;conservo R2 sulla prima parola di RESULT
		STR		R3, [R0, #4] ;conservo R3 (indirizzo del minimo)sulla seconda parola di RESULT
		                       ;(non capisco perchè sia necessario, ma ok)
		
		END
		
		
		;sottoprogramma per il minimo
CALCMIN	STMFD	SP!, {R0, R1, R2, R3, R4, R12} ;store multipla per conservare sullo stack dei registri temporanei
		                                         ;(virtualmente illimitati)
		ADD		R12, SP, #20 ;aggiungo 20 a SP e metto la somma su R12 in modo da far avere su R12
	                        	   ;un puntatore a sè stesso sullo stack
		LDR		R0, [R12, #4] ;carico su R0 il valore del vecchio R0, in pratica è inutile
	             	              ;(prova a togliere sto comando e non cambia niente)
		LDR		R1, [R12, #8] ;carico su R1 il valore del vecchio R1, anche questo è inutile e se lo togli non cambia niente
		
		LDR		R2, [R0] ;carico su R2 il primo valore dell'array
		MOV		R3, R0 ;copio su R3 l'indirizzo del primo valore dell'array (inutile)
		
		ADD		R0, R0, #4 ;aggiorno l'indirizzo del puntatore agli elementi dell'array
		SUB		R1, R1, #1 ;decremento il contatore degli elementi dell'array
		
CICLOM	CMP		R1, #0 ;controllo se il contatore è 0
		BEQ		FINEM ;in caso abbiamo finito
		LDR		R4, [R0] ;carico su R4 l'elemento dell'arrya successivo a quello di R2
		CMP		R2, R4 ;confronto R2 con R4
		BLE		FINEC ;se R2 <= R4, vado direttamente a FINEC
		MOV		R2, R4 ;copio su R2 il valore di R4 perchè a questo punto R4 < R2
		MOV		R3, R0 ;copio su R3 l'indirizzo del nuovo possibile minimo (inutile)
FINEC	ADD		R0, R0, #4 ;aggiorno l'indirizzo e punto all'elemento successivo nell'array
		SUB		R1, R1, #1 ;decremento il contatore
		B		CICLOM ;torno indietro a CICLOM
		
FINEM	STR		R2, [R12, #4] ;conservo R2 (minimo) sullo stack
		STR		R3, [R12, #8] ;corserva R3 (indirizzo del minimo) sullo stack (inutile)
		LDMFD	SP!, {R0, R1, R2, R3, R4, R12} ;ricarica i vecchi valori dei registri conservati sullo stack
		
		MOV		PC, LR ;ripristina PC con l'indirizzo di LR, usciamo dal sottoprogramma
