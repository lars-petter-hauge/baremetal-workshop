# Assembly cheatsheet

## Basic program structure

```assembly
.global _start

_start:
    // Your program starts here

main:
    // Add your code
    B main // Infinite loop to prevent program from exiting
```

## Patterns

### For loop

```assembly
.global _start

_start:
    MOV R0, #9         // Loop counter
loop:
    // Your code here
    SUB R0, R0, #1      // Decrement counter
    CMP R0, #0          // Check if counter reached 0
    BNE loop            // Repeat if not zero

main:
    B main
```

### delay loop

```assembly
delay:
    LDR R0, =4000000    // Set delay count
waitloop:
    SUBS R0, R0, #1     // Decrement counter
    BNE waitloop        // Repeat until counter is zero
    BX LR               // Return from subroutine
```

### Loading values

```assembly
.global _start
.equ CONSTANT, 0xFF200000
_start_:
    LDR R0, =4000000    // Use equal sign for values too large to be an immediate value. A pseudo instruction.
    LDR R0, #16         // Loads register with decimal 16. Immediate values are prefixed with hash.
    LDR R0, #0xB        // Loads register with hexadecimal value 11. Immediate value.
    LDR R0, 0b1011      // Loads register with binary value of 11. Immediate value.
    LDR R0, =0xFF200000 // Loads register with hexadecimal value that corresponds to address in memory.
    LDR R0, =CONSTANT // Loads register with CONSTANT. .equ is a directive that allows you to define constants with a symbolic name. Assembler will replace symbolic name with actual value when compiling.
```

[What is a pseudo-instructions?](questions.md#what-are-pseudo-instructions)
[What is an immediate?](questions.md#what-is-an-immediate-value)

### Managing link register when calling subroutines

Especially when calling a subroutine within a subroutine it is useful to put LR on the stack by using `PUSH`and `POP`

```assembly
.global _start

_start:
    BL subroutine

subroutine:
    PUSH {LR}
    BL nested_subroutine
    POP {LR}
    BX LR

nested_subroutine: 
  PUSH {LR}
  BL inner
  POP {LR}
  BX LR

inner: 
  //code
  BX LR

main:
    B main
```

## Instructions

### Moving Data

#### **MOV**  

Move a value into a register.

**Syntax:**  
`MOV Rd, #value` – Move an immediate value into a register.  
`MOV Rd, Rm` – Copy the value from one register to another.
`LDR Rd, =value` – Shorthand for loading constant into register (pseudo-instruction, which assembler translates to more instructions depending on value being loaded)

**Examples:**  

```assembly
MOV R0, #5     // Load the immediate value 5 into R0
MOV R1, R0     // Copy the value in R0 to R1
```

#### **LDR**  

Load a value from memory into a register.

**Syntax:**

`LDR Rd, =value` – Load an immediate (or constant) value into a register.
`LDR Rd, [Rn]` – Load a value from the memory address in Rn into Rd.

**Examples:**

```assembly
LDR R0, =100   // Load the immediate value 100 into R0
LDR R1, [R2]   // Load the value from the memory address in R2 into R1
LDR R2, =0xF4240 // Load the constant 1000000 into R2
```

#### **STR**  

Store a value from a register into memory.

**Syntax:**

`STR Rd, [Rn]` – Store the value in Rd into the memory address in Rn.

**Examples:**

```assembly
LDR R0, =0xFF200000  // Load memory address into R0
MOV R1, #1           // Load the value 1 into R1
STR R1, [R0]         // Store the value in R1 to the address in R0
```

### Arithmetic and Logic

#### **ADD**  

Add two values and store the result in a register.

**Syntax:**

`ADD Rd, Rn, Rm` – Add the values in Rn and Rm and store in Rd.
`ADD Rd, Rn, #value` – Add an immediate value to Rn and store in Rd.

**Examples:**

```assembly
MOV R1, #1
MOV R2, #2
ADD R0, R1, R2       // Add R1 and R2, store result in R0
ADD R3, R1, #10      // Add 10 to R1, store result in R0
```

#### **SUB**  

Subtract one value from another and store the result in a register.

**Syntax:**

`SUB Rd, Rn, Rm` – Subtract the value in Rm from Rn and store in Rd.
`SUB Rd, Rn, #value` – Subtract an immediate value from Rn and store in Rd.

**Examples:**

```assembly
MOV R1, #8
MOV R2, #3
SUB R0, R1, R2       // Subtract R2 from R1, store result in R0
SUB R3, R1, #6       // Subtract 5 from R1, store result in R0
```

#### **CMP**  

Compare two values and update condition flags. Flags include Z (Zero), C (Carry or unsigned overflow), N (Negative), V (Signed overflow)

In essence it performs **Rn minus Rm (or Rn - #value)**. The result of that will set N, Z, C and V. This allows us to figure out if values are equal, greater or less.
This instruction is typically followed by a conditional branch instruction `BEQ`, `BNE`, `BGT` and `BLT`

**Syntax:**

`CMP Rn, Rm` – Compare the values in Rn and Rm.
`CMP Rn, #value` – Compare the value in Rn with an immediate value.

**Examples:**

```assembly
MOV R0, #10
MOV R1, #11
CMP R0, R1           // Compare R0 and R1
CMP R0, #10          // Compare R0 with the value 10
```

### Branching

#### **B**  

Unconditional branch to a label.

**Syntax:**

`B label` – Branch to the specified label.

**Examples:**

```assembly
B loop               // Branch to the label "loop"
```

#### **BL**  

Branch to a subroutine. Saves the return address in the link register (LR).

**Syntax:**

`BL subroutine` – Branch to the specified subroutine.

**Examples:**

```assembly
_start:
  BL delay             // Call the subroutine "delay"

delay:
  // ...code
  BX LR // return to address stored in link register
```

#### **BEQ**  

Branch if equal (Zero flag is set).

**Syntax:**

`BEQ label` – Branch to the specified label if the Zero flag is set.

**Examples:**

```assembly
CMP R0, #5           // Compare R0 with 5
BEQ equal_label      // Branch to "equal_label" if R0 == 5
```

#### **BNE**  

Branch if not equal (Zero flag is clear).

**Syntax:**

`BNE label` – Branch to the specified label if the Zero flag is clear.

**Examples:**

```assembly
CMP R0, #5           // Compare R0 with 5
BNE not_equal_label  // Branch to "not_equal_label" if R0 != 5
```
