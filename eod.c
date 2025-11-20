#include <stdint.h>
#define AUDIO_BASE       0xFF203040  // Audio device
#define PUSHBUTTON_BASE  0xFF200050  // Push buttons

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

// Play a short beep using the audio device
void beep(void) {
    volatile int *audio_ptr = (int *)AUDIO_BASE;
        
	int tone = 10; // Default tone (A4); // Frequency control (lower = higher pitch)
    int duration = 1000; // Number of samples

	// Read push buttons to determine tone frequency
    int btn = read_pushbuttons();
    
	if (btn == 1) tone = 50; // C5
    else if (btn == 2) tone = 100; // D5
    else if (btn == 4) tone = 200; // E5
    else if (btn == 8) tone = 400; // G5

	
    for (int i = 0; i < duration; i++) {
        // Wait until there is space in the FIFO
        while ((audio_ptr[1] & 0xFF) == 0); // Left FIFO space
        while ((audio_ptr[1] & 0xFF00) == 0); // Right FIFO space

        // Write same sample to left and right channels
        int sample = (i / tone % 2) ? 0x7FFFFFFF : 0x80000000;
        audio_ptr[2] = sample; // Left
        audio_ptr[3] = sample; // Right
    }
}

// Read push buttons (returns 0–15)
int read_pushbuttons() {
    volatile uint32_t *KEY_ptr = (uint32_t *)PUSHBUTTON_BASE;
    return *KEY_ptr & 0xF;
}

int main(void)
{
    int timer = 20;

    while (timer >= 0)
    {
        writeNumber(timer); // update HEX display
        beep();
        delay(5000000);     // ~1 second delay (adjust for your clock)
        timer--;
    }

    while (1)
        ; // hold final display

    return 0;
}
