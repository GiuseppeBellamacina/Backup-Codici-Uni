ARR1		DCD		2,0,3,1,5,4 ;creo il primo array
ARR2		DCD		0,6,2,6,1,3 ;creo il secondo array
NUMEL	DCD		6 ;dimensione di ogni array
RESULT	FILL		4 ;libero spazio per il risultato finale
		
		MOV		R0, #ARR1 ;copio su R0 l'indirizzo del primo elemento del primo array
		MOV		R1, #ARR2 ;copio su R1 l'indirizzo del primo elemento del secondo array
		
		MOV		R2, #NUMEL ;copio su R2 l'indirizzo della dim degli array
		LDR		R2, [R2] ;carico su R2 la dim dell'array
		
		STMFD	SP!, {R0, R1, R2} ;store multipla per impilare 3 registi sullo stack
		BL		PRODS ;chiamata al sottoprogramma del prodotto scalare
		LDR		R0, [SP], #12 ;carico su R0 l'indirizzo di SP e incremento di 12 (spilo tutto)
		
		MOV		R1, #RESULT ;copio su R1 l'indirizzo del risultato
		STR		R0, [R1] ;conservo R0 su RESULT
		
		END
		
		;sottoprogramma	prodotto scalare
PRODS	STMFD	SP!, {R0, R1, R2, R3, R4, R5, R12, LR} ;impilo questi registri (attenzione a LR)
		ADD		R12, SP, #24 ;metto su R12 l'indirizzo di pila di R12
		LDR		R0, [R12, #8] ;carico su R0 il valore di R0 presente sulla pila (lo stesso valore)
		LDR		R1, [R12, #12] ;carico su R1 il valore di R1 presente sulla pila
		LDR		R2, [R12, #16] ;carico su R2 il valore di R2 presente sulla pila
		
		MOV		R3, #0 ;azzero R3 (prodotto scalare parziale)
		
CICLOPS	CMP		R2, #0 ;confronto R2 (contatore dim array) con lo 0
		BEQ		FINEPS ;se R2 == 0 allora vado a FINEPS
		LDR		R4, [R0], #4 ;carico su R4 il primo el del primo array e aggiungo 4 a R0
		LDR		R5, [R1], #4 ;carico su R5 il primo el del secondo array e aggiungo 4 a R1
		STMFD	SP!, {R4, R5} ;conservo R4 e R5 sullo stack
		BL		MULT ;vado al secondo sottoprogramma
		LDR		R4, [SP], #8 ;carico su R4 il valore dell'R4 conservato alla linea 61 ed eseguo il pop di R4 ed R5 della pila
		ADD		R3, R3, R4 ;aggiungo R4 ad R3
		SUB		R2, R2, #1 ;decremento il contatore
		B		CICLOPS ;torno indietro
		
FINEPS	STR		R3, [R12, #8] ;conservo R3 sull'R0 della pila 2 posti sotto R12 (quello basso basso)
		LDMFD	SP!, {R0, R1, R2, R3, R4, R5, R12, LR} ;spilo questi registri ripristinandone i valori iniziali
		MOV		PC, LR ;esco dal sottoprogramma e torno alla riga 14
		
		;sottoprogramma	moltiplicazione
		
MULT		STMFD	SP!, {R0, R1, R2, R12} ;carico questi registri temporanei sulla pila
		ADD		R12, SP, #12 ;metto su R12 l'indirizzo di pila dell'R12 appena impilato
		LDR		R0, [R12, #4] ;carico su R0 il valore dell'R4 precedentemente impilato (elem arr1)
		LDR		R1, [R12, #8] ;carico su R1 il valore dell'R5 precedentemente impilato (elem arr2)
		
		MOV		R2, #0 ;azzero R2 (somma parziale che diventa prodotto tra i-esimo el del primo array
					  ;e i-esimo el del secondo array)
		
CICLOM	CMP		R1, #0 ;confronto R1 con 0
		BEQ		FINEM ;se R1 == 0 vado avanti fino a FINEM
		ADD		R2, R2, R0 ;sommo R0 a R2
		SUB		R1, R1, #1 ;decremento il contatore (equivale all'elem considerato dell'array2)
		B		CICLOM ;torno indietro a CICLOM
		
FINEM	STR		R2, [R12, #4] ;conservo R2 sull'R4 della pila
		LDMFD	SP!, {R0, R1, R2, R12} ;ripristino i vecchi valori (valori del primo sottopr) di questi registri
		
		MOV		PC, LR ;torno al sottopr n1 (linea 36)
