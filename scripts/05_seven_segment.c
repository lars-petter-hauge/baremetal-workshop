#include <stdint.h>

volatile uint32_t * LEDS = (uint32_t*)0xFF200020;
volatile uint32_t * BUTTONS = (uint32_t*)0xFF200050;

const unsigned char seven_seg_lookup_active_high[16] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // b
    0x39, // C
    0x5E, // d
    0x79, // E
    0x71  // F
};


void wait(void) {
    volatile int i;
    for (i = 0; i < 3000000; i++);
}


int main(void)
{
	while (1){
		while (*BUTTONS == 0);
		for (int i = 9; i >= 0; i--)
		{
			*LEDS = seven_seg_lookup_active_high[i];
			wait();
		}
	}
}