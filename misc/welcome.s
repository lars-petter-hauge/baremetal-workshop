.equ CHAR_BASE, 0xC9000000
equinor_string:
	.asciz "Welcome"
	.asciz "to bare"
	.asciz "metal "
	.asciz "progra"
	.asciz "mming"

_start:
    LDR R2, =CHAR_BASE
	MOV R0,#5
    MOV R1,#30
    LDR R3, =equinor_string
    BL draw_string

main:
	B main

draw_string:
	LDRB R4, [R3], #1
	CMP R4, #0
	BEQ draw_string_end
	PUSH {LR, R2}
	BL draw_char
	POP {LR, R2}
	ADD R0, R0, #1
	B draw_string

draw_string_end:
	BX LR

draw_char:
    ADD R2, R2, R1, LSL #7
    ADD R2, R2, R0
    STRB R4, [R2]
    BX LR