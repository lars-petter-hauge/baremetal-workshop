.equ TIMER_BASE, 0xFFFEC600
.equ LED_BASE,   0xFF200000

.global _start
_start:
	LDR R0, =LED_BASE
	MOV R2, #0b0
	LDR R1, =TIMER_BASE
	LDR R3, =200000000
	STR R3, [R1]
	MOV R3, #0b011
	STR R3, [R1, #0x8] // Store pattern in R3 0xFFFEC608. Sets E and A flag
loop:
	STR R2, [R0]
wait:
	LDR R3, [R1, #0xC] //Load word at 0xFFFEC60C with F flag into R3. When F flag is 1, the timer has expired.
	CMP R3, #0
	BEQ wait

	STR R3, [R1, #0xC]
	EOR R2, R2, #0b1
	B loop