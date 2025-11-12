.global _start



.section .data    
.equ VGA_BASE, 0xC8000000
.equ SCREEN_WIDTH, 320
.equ SCREEN_HEIGHT, 240
.equ BLACK, 0x0000
.equ CHAR_BASE, 0xC9000000
.align 4                     @ Align the string to a 4-byte boundary
equinor_string:
    .asciz "Welcome to bare metal programming"

.section .text               @ Start the code section
.align 4                     @ Align the code to a 4-byte boundary
_start:
   
	BL clear_screen
    BL draw_string_start

main:
	B main

draw_string_start:
 	LDR R2, =CHAR_BASE
	MOV R0,#20
    MOV R1,#30
    LDR R3, =equinor_string
	ADD R2, R2, R1, LSL #7
	ADD R2, R2, R0

draw_string:
	BL delay
	LDRB R4, [R3], #1
	CMP R4, #0
	BEQ draw_string_end

    STRB R4, [R2]
	ADD R0, R0, #1
	ADD R2, R2, #1
	B draw_string
	

draw_string_end:
	BX LR

clear_screen:
	MOV R1, #0

clear_row:
	MOV R0, #0

clear_pixel:
	LDR R2, =VGA_BASE
	ADD R2, R2, R1, LSL #10
	ADD R2, R2, R0, LSL #1
	LDR R3, =BLACK
	STRH R3, [R2]
	ADD R0, R0, #1
	CMP R0, #SCREEN_WIDTH
	BLT clear_pixel
	ADD R1, R1, #1
	CMP R1, #SCREEN_HEIGHT
	BLT clear_row

	BX LR
	
delay:
    PUSH {R4}
    MOV R4, #0xFFFF

delay_loop:
    SUBS R4, R4, #1
    BNE delay_loop
    POP {R4}
    BX LR
