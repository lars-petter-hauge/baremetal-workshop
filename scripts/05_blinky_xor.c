#include <stdint.h>

volatile uint32_t * LEDR = (uint32_t*)0xFF200000;

void wait(void) {
    volatile int i;
    for (i = 0; i < 3000000; i++);
}

int main(void)
{
	while (1) {
        *LEDR ^= 0b1;
		wait();
	}
}
