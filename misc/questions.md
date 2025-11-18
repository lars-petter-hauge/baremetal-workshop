# Questions

## What are pseudo-instructions?

`LDR Rx, =0xFF200000` is a pseudo-instruction. The assembler allows some convenience or abstraction. In this case we can load a register with values that are too big (cannot be represented as immediate values) to fit as an immediate value.
Assembler will use the literal pool to store constant values. This is like a lookup table.

- What `LDR Rx, =0xFF200000`does:

```assembly
.global _start

_start:
    ADR R1, literal_pool
    LDR R1, [R1]

    MOV R0, #0b11
    STR R0, [R1]

loop:
    B loop

literal_pool:
    .word 0xFF200000

```

First address of the **literal_pool** is loaded into `R1`, then we load the `R1` with the content of **literal_pool** address, which means it contains the `=0xFF200000`

If you have more than one value in the **literal_pool** you `LDR`with offset.
`LDR R2, [R0, #4]` - 4 bytes offset to next word since word consists of 32 bits or 4 bytes.

## What is an immediate value?

An immediate value is a constant that is directly encoded into an instruction. Instead of loading a value from memory or a register, the CPU uses the immediate value directly as part of the instruction.

In DE1-SoC we have 32bit instructions or opcodes. After you compile a program you can see your program stored in memory. Content of a memory address holds an instructions of 32 bits. This bit pattern must encode which instruction, what register it targets in addition to an immediate value, which limits the number of bits that can be used for an immediate value.

12 bits (16 bits for `MOV`) of an instructions is reserved for the immediate value of which:
8 bits define the constant, and 4 bits to rotate value right.

The assembler will complain if you try to use a value that cannot be encoded as an immediate value like this:

```assembly
.global _start
_start:
  ADD r0, r1, #0b111111111 // 13 bits, cannot be rotated
  ADD r0, r1, #0b111111110 // Works since we can right rotate
  ADD r0, r1, #0b111111110000000000000000 // Works since we can right rotate
```

```bash

Error: invalid constant (1ff) after fixup
```

```assembly

