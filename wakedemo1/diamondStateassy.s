	.arch msp430g2553
	.p2align 1,0

	.text
	.extern diamondShape
	
	.data
	
diaState:
	.word 0		;

	
jt:
	.word case0 	; jt[0]
	.word case1
	.word case2
	.word case3
	.word default
	
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
	call #diamondShape
	mov #110, r12
	mov #110, r13
	mov #0xf800, r14
	call #diamondShape
	mov #120, r12
	mov #120, r13
	mov #0xf800, r14
	call #diamondShape
	add #1, diaState
	jmp end
case1:
	mov #100, r12
	mov #100, r13
	mov #0xd012, r14
	call #diamondShape
	add #1, diaState
	jmp end
case2:
	mov #100, r12
	mov #100, r13
	mov #0xf800, r14
	call #diamondShape
	mov #110, r12
	mov #110 , r13
	mov #0x2116, r14
	call #diamondShape
	add #1, diaState
	jmp end
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
	mov #0, &diaState
	jmp end
end:
	pop r0
	
