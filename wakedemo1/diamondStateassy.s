	.arch msp430g2553
	.p2align 1,0

	.text
	.extern diamondShape 
	
	.data
	
diaState:
	.word 0		;

	
jt:
	.word case0 	; jt[0]
	.word case1	; jt[1]
	.word case2	; jt[2]
	.word case3	; jt[3]
	.word default	; jt[4]
	
	.global diamond_State
	
diamond_State:
	cmp #5, &diaState	; diaState-5 if >4 jump
	jhs   default
	mov &diaState, r12	;
	add   r12, r12 		; r12*2
	mov   jt(r12), r0 	; jump jt(diaState)

case0:
	mov #100, r12
	mov #100, r13
	mov #0xf800,r14
	call #diamondShape 	;diamondShape(100,100, color blue)
	mov #110, r12
	mov #110, r13
	mov #0xf800, r14
	call #diamondShape 	;diamondShape(110,110, color blue)
	mov #120, r12
	mov #120, r13
	mov #0xf800, r14
	call #diamondShape 	;diamondShape(120,120, color blue)
	add #1, &diaState 	; diastate++
	jmp end
case1:
	mov #100, r12
	mov #100, r13
	mov #0xd012, r14
	call #diamondShape 	;diamondShape(100,100 0xd012)
	add #1, &diaState
	jmp end			;pop r0
case2:
	mov #100, r12
	mov #100, r13
	mov #0xf800, r14
	call #diamondShape
	mov #110, r12
	mov #110 , r13
	mov #0x2116, r14
	call #diamondShape 	;diamondShape(110, 110, 0x2116)
	add #1, &diaState	;diaState++
	jmp end			;pop r0
case3:
	mov #100, r12
	mov #100, r13
	mov #0xf800, r14
	call #diamondShape
	mov #110, r12
	mov #110, r13
	mov #0xf800, r14
	call #diamondShape
	mov #120, r12
	mov #120, r13
	mov #0x1b5a, r14
	call #diamondShape
	mov #0,  &diaState
	jmp end
default:
	mov #0, &diaState	;diaState =0
	jmp end
end:
	pop r0 		
	
