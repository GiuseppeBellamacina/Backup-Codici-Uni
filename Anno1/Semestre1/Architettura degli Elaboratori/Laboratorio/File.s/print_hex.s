				
				
digit_map			dcb		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B','C','D','E','F'
				
hex_value			dcd		0,0,0,0,0
				
				;		R0 = value;
				;		R1 = hex_value
				;		R2 = i
				;		R3 = digit_value
				;		R4 = digit_char
				;		R5 = digit_map
				
				mov		r0,#1
				lsl		r0,r0,#8
				add		r0,r0,#3
				mov		r1,#hex_value
				add		r1,r1,#3
				mov		r2,#3
				
print_hex_loop
				cmp		r2,#0
				blt		end_print_hex_loop
				
				and		r3, r0, #0x0f
				
				mov		r5,#digit_map
				add		r5,r5,r3
				ldrb		r4,[r5]
				;		char digit_char = digit_map[digit_value];
				
				strb		r4,[r1]
				
				lsr		r0,r0,#4
				
				sub		r1,r1,#1
				sub		r2,r2,#1
				b		print_hex_loop
				
end_print_hex_loop
				end
				
