# Bare Metal C Cheat Sheet


## Minimal bare-metal program structure
```c
#include <stdint.h>

int main(void) {
    // Your code here

    while (1) {
        // Endless loop so the program never "exits"
    }
}
```

## Basic patterns

### For-loop (countdown)
```c
for (int i = 9; i >= 0; i--) {
    // Your code here
}
```

### Conditional loop

```c
int counter = 9;

while (counter != 0) {
    // loop body

    counter--;   // decrement
}
```

### Busy-wait delay

Use a simple loop that just burns CPU cycles:

```c
void delay(volatile uint32_t count) {
    while (count--) {
        // Do nothing, just wait
    }
}

int main(void) {
    while (1) {
        // ...
        delay(4000000);   // Rough delay
        // ...
    }
}
```

`volatile` prevents the compiler from optimizing the loop away.

### Bitwise Operators

#### AND - `&`
Used to clear bits or test if bits are set.

```c
uint32_t x = 0b1101u;      // 13
uint32_t y = x & 0b0100u;  // result = 0b0100 (4)
```

Turn off LED bit 0:

```c
*LEDR &= ~1u;   // clear bit 0
```

#### OR - `|`
Used to set bits

```c
uint32_t x = 0b0101;
x |= 0b1000;    // x becomes 0b1101
```

Turn ON LED bit 0:

```c
*LEDS |= 1u;    // set bit 0
```

#### XOR - `^`

Flip bits (toggle)

```c
uint32_t x = 0b1010;
x ^= 0b1111;    // becomes 0b0101
```

Toggle LED 0:

```c
*LEDS ^= 1u;    // toggle LEDR0
```

#### NOT - `~`

```c
uint8_t x = 0b00001111;
uint8_t y = ~x;   // becomes 0b11110000
```

Clear a bit using NOT + AND:

```c
*LEDR &= ~(1u << 3);   // clear bit 3
```

#### Left shift - `<<`

Moves bits left (multiply by 2 each shift).

```c
uint32_t x = 1u << 5;   // equals 0b100000 (32)
```

Turn on LED number n:

```c
int n = 4;
*LEDR |= (1u << n);
```

#### Right Shift — `>>`

Moves bits right (divide by 2 each shift).

```c
uint32_t x = 0b100000;
x >>= 1;   // becomes 0b010000
```

### Functions

```c
void myfunction(void) {
    // Your code here
}
```

No manual stack or return-address management is needed.

## Memory-mapped I/O (read/write hardware registers)

Use pointers to fixed addresses:

```c
#include <stdint.h>

#define LED_BASE   0xFF200000u  // example address
#define LEDS       (*(volatile uint32_t *)LED_BASE)

int main(void) {
    LEDS = 1;   // turn on LED 0

    while (1) {
    }
}
```

`volatile` tells the compiler this memory can change outside the program (hardware).

`*(volatile uint32_t *)LED_BASE` is “the 32-bit register at this address.”

## Arithmetic and logic

### Addition

```c
int a = 1;
int b = 2;
int sum1 = a + b;     // add variables
int sum2 = a + 10;    // add immediate
```

### Subtraction

```c
int a = 8;
int b = 3;
int diff1 = a - b;    // subtract variable
int diff2 = a - 6;    // subtract immediate
```

### Comparison (sets up for branching)

```c
int x = 10;
int y = 11;

int equal      = (x == y);
int not_equal  = (x != y);
int greater    = (x > y);
int less       = (x < y);
```