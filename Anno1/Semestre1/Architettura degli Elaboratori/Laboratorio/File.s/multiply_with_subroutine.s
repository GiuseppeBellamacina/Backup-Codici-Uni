			
			
			MOV		R5,#10	; primo operando
			STMDA	R13!,{R5} ; PUSH R5
			MOV		R5,#30    ; secondo operando
			STMDA	R13!,{R5} ; PUSH R5
			BL		multiply
			ADD		R13,R13,#8
			;		R0 sara' il prodotto tra 10 e 30
			end
			
			
multiply
			stmdb	r13!,{r1,r2,r3,r4,r5}
			
			ldr		r0,[r13,#24]
			ldr		r1,[r13,#28]
			
			mov		r2,#0	 ;;i
			mov		r3,#0      ;;p
			
loop
			cmp		r2,#8
			beq		end_multiply
			and		r4,r1,#0x1
			cmp		r4,#0
			beq		no_sum
			
			LSL		r5,r0,#8
			add		r3,r3,r5
no_sum
			lsr		r3,r3,#1
			
			lsr		r1,r1,#1
			add		r2,r2,#1
			b		loop
			
			
end_multiply
			mov		r0,r3 ; copy result onto R0
			ldmia	r13!,{r1,r2,r3,r4,r5}
			mov		pc,lr
			
