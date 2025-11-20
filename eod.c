#include <stdint.h>

volatile uint32_t *HEX3_HEX0 = (uint32_t *)0xFF200020; // HEX3–0

const int segmentLookup[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// Simple software delay (~1 second)
void delay(volatile int count)
{
    while (count--)
        ;
}

// Write a number 0–99 to HEX1–0
void writeNumber(int number)
{
    int tens = number / 10;
    int ones = number % 10;

    uint32_t value = (segmentLookup[tens] << 8) | segmentLookup[ones];
    *HEX3_HEX0 = value;
}

int main(void)
{
    int timer = 20;

    while (timer >= 0)
    {
        writeNumber(timer); // update HEX display
        delay(5000000);     // ~1 second delay (adjust for your clock)
        timer--;
    }

    while (1)
        ; // hold final display

    return 0;
}
