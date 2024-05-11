Size_a	DCD		7
Array_a	DCD		1,3,10,2,7,9,20

Size_b	DCD		0
Array_b	DCD		0,0,0,0,0,0,0
		;
		;		R0 = dimensione array a
		;		R1 = ptr array a
		;		R2 = ptr array b
		;		R3, R4 = estremi intervallo
		;		R5 = contatore elementi compresi nell'intervallo
		;		
		;
		MOV		R2,#0
		MOV		R5,#0
		
		MOV		R3, #7
		MOV		R4, #20
		
		MOV		R0, #Size_a
		LDR		R0,[R0]
		
		MOV		R1,#Array_a
		MOV		R2,#Array_b
		
loop
		CMP		R0, #0
		BEQ		end_loop

		; PUSH R0
		STMDA	R13!, {R0}
		
		LDR		R0, [R1]
		
		CMP		R0, R3 ;; confronto con estremo inferire
		BLT		skip ;; se minore, non lo considero
		CMP		R0, R4 ;; confronto con estremo superiore
		BGT		skip ;; se maggiore, non lo considero
		
		ADD		R5, R5, #1
		STR		R0, [R2]
		ADD		R2, R2, #4
		
skip
		; POP R0
		LDMIB	R13!, {R0}
		
		SUB		R0,R0,#1
		ADD		R1,R1,#4
		B		loop
end_loop
		MOV		R2,#Size_b
		STR		R5, [R2]		
		end
		
