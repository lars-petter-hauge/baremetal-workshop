# Baremetal programming

---

## What is it?

- Bullet point 1
- Bullet point 2

---

## Exercise: Why do it?

---

---

## Why do it?

- Demystifies how a computer works.
- Good domain to get experience learning something new with the help of an LLM.
- Understanding the basics can help you in your work
- Why not - It is different, it has potential to be fun.

---

## DE1-SoC simulator

Light up a LED, and get familiar with the simulator

```assembly
.global _start

.equ LEDR_BASE, 0xFF200000

_start:
    ldr     r0, =LEDR_BASE

blink_loop:
    mov     r1, #1
    str     r1, [r0]
    mov     r1, #0
    str     r1, [r0]
    b       blink_loop
```

---

## DE1-SoC simulator, part two

Add a delay to make LED blink

```assembly
.global _start

.equ LEDR_BASE, 0xFF200000

_start:
    ldr     r0, =LEDR_BASE

blink_loop:
    mov     r1, #1
    str     r1, [r0]
    bl      delay

    mov     r1, #0
    str     r1, [r0]
    bl      delay

    b       blink_loop

delay:
    ldr     r2, =10000000

waitloop:
    sub     r2, #1
    cmp     r2, #0
    bne     waitloop
    bx      lr
```

---

## DE1-SoC simulator, part three

Reading switches from memory-mapped I/O and turn on LEDs

```assembly
.global _start

.equ LEDR_BASE, 0xFF200000
.equ SW_BASE, 0xFF200040

_start:
    ldr     r0, =LEDR_BASE
    ldr     r4, =SW_BASE

switch_loop:
    ldr     r3, [r4]
    str     r3, [r0]

    b       switch_loop

```

---

## DE1-SoC simulator, part four

Push button and show YES in seven-segment display

---

## Educational or realistic?

---

## Use LLM as a tutor

[chat.equinor.com](https://chat.equinor.com) will be your tutor.

- Can you instruct the LLM to create a personalized learning experience?
- Can it generate full solutions for you?
- In what way was the LLM helpful, and when did it only bring you confusion?

---

## What's next?

Use the simulator, experiment, add breakpoints and debug, inspect the memory.

- If you make something, please send us the script.

---
