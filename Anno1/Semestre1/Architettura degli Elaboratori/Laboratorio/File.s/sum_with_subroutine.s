		
		
		MOV		R5,#100	; primo operando
		STMDA	R13!,{R5} ; PUSH R5
		MOV		R5,#300	; secondo operando
		STMDA	R13!,{R5} ; PUSH R5
		BL		sum
		ADD		R13,R13,#8
		;		R0 sara' la somma tra 100 e 300
		end
		
		
sum
		STMDA	R13!,{R1} ; PUSH R1
		LDR		R0,[R13,#12]
		LDR		R1,[R13,#8]
		ADD		R0,R0,R1
		LDMIB	R13!,{R1} ; POP R1
		MOV		PC,LR
		
		
		
