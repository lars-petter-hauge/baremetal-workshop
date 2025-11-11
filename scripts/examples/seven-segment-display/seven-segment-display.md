# Seven segment display

- At base address `0xFF200020`you find the seven segment displays.
- Each bit activates a segment in the display. See image below:

![segments indices](./images/segments.png)

- Example below we display number four in the rightmost display:

```assembly
.equ SEGMENT_BASE, 0xFF200020

.global _start
_start:
  LDR R0, =SEGMENT_BASE
  MOV R1, #0b1100110 // Pattern to draw four in rightmost segment
  STR R1, [R0]

end:
  B end
```

## Task - Draw number 2

Here you need to make a new bit pattern that will make the display draw two.

<details>
  <summary>Click for a solution</summary>

```assembly
.equ SEGMENT_BASE, 0xFF200020

.global _start
_start:
  LDR R0, =SEGMENT_BASE
  MOV R1, #0b1011011 // Pattern to draw four in rightmost segment
  STR R1, [R0]

end:
  B end
```

</details>
