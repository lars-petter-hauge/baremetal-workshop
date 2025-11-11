#include <stdint.h>
#include <string.h>

#define VGA_PIXEL_BASE  ((volatile uint16_t *)0xC8000000) // pixel buffer (HPS)
#define VGA_CHAR_BASE   ((volatile char *)0xC9000000)     // text buffer (HPS)

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240
#define PIXEL_STRIDE    512

#define CHAR_COLS       80
#define CHAR_ROWS       60
#define CHAR_STRIDE     128

#define CELL_W 4
#define CELL_H 4

// ------------ fast PRNG for coordinates ------------
static uint32_t rng = 0x1234ABCDu;
static inline uint32_t xorshift32(void) {
    uint32_t x = rng;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng = x;
    return x;
}

// ------------ hash for color (soft color noise) ------------
static inline uint32_t mix32(uint32_t x) {
    x += 0x9E3779B9u;
    x = (x ^ (x >> 16)) * 0x85EBCA6Bu;
    x = (x ^ (x >> 13)) * 0xC2B2AE35u;
    return x ^ (x >> 16);
}
static inline uint8_t clamp_u8(int v){ return (v<0)?0:(v>255)?255:(uint8_t)v; }

// Subtle color noise: grayscale base + small RGB tints
static inline uint16_t noise_color_soft565(uint32_t tick, int x, int y) {
    uint32_t n = (uint32_t)(y * PIXEL_STRIDE + x) ^ (tick * 0x9E3779B1u);
    uint32_t v = mix32(n);

    uint8_t base = (uint8_t)v;        // 0..255 gray
    const int TINT = 24;              // tune: 16 (subtle) .. 48 (richer)
    int dr = (((int)((v >>  8) & 0xFF) - 128) * TINT) / 128;
    int dg = (((int)((v >> 16) & 0xFF) - 128) * TINT) / 128;
    int db = (((int)((v >> 24) & 0xFF) - 128) * TINT) / 128;

    uint8_t r8 = clamp_u8((int)base + dr);
    uint8_t g8 = clamp_u8((int)base + dg);
    uint8_t b8 = clamp_u8((int)base + db);

    return (uint16_t)((r8>>3)<<11 | (g8>>2)<<5 | (b8>>3));
}

// ------------ simple drawing helpers ------------
static void draw_filled_rect_px(int x, int y, int w, int h, uint16_t color) {
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x + w > SCREEN_WIDTH)  w = SCREEN_WIDTH  - x;
    if (y + h > SCREEN_HEIGHT) h = SCREEN_HEIGHT - y;
    if (w <= 0 || h <= 0) return;
    for (int yy = 0; yy < h; ++yy) {
        volatile uint16_t *row = VGA_PIXEL_BASE + (y + yy) * PIXEL_STRIDE + x;
        for (int xx = 0; xx < w; ++xx) row[xx] = color;
    }
}

static void VGA_text(int x, int y, const char *s) {
    int offset = y * CHAR_STRIDE + x;
    while (*s) VGA_CHAR_BASE[offset++] = *s++;
}

// Optional: one-time masked fill so you start with a full background
static void initial_fill_soft_color_with_mask(uint32_t tick, int bx, int by, int bw, int bh) {
    int mx0 = bx, mx1 = bx + bw; if (mx0 < 0) mx0 = 0; if (mx1 > SCREEN_WIDTH) mx1 = SCREEN_WIDTH;
    int my0 = by, my1 = by + bh; if (my0 < 0) my0 = 0; if (my1 > SCREEN_HEIGHT) my1 = SCREEN_HEIGHT;

    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        volatile uint16_t *row = VGA_PIXEL_BASE + y * PIXEL_STRIDE;
        if (y >= my0 && y < my1) {
            for (int x = 0; x < mx0; ++x) row[x] = noise_color_soft565(tick, x, y);
            for (int x = mx1; x < SCREEN_WIDTH; ++x) row[x] = noise_color_soft565(tick, x, y);
        } else {
            for (int x = 0; x < SCREEN_WIDTH; ++x) row[x] = noise_color_soft565(tick, x, y);
        }
    }
}

// ------------ main ------------
int main(void) {
    const char *msg = "Welcome to baremetal programming";

    // Place text
    int x_chars = (CHAR_COLS - (int)strlen(msg)) / 2; if (x_chars < 0) x_chars = 0;
    int y_chars = CHAR_ROWS / 2;
    VGA_text(x_chars, y_chars, msg);

    // Black text box (in pixels)
    const int pad_x_cells = 2, pad_y_cells = 1;
    int text_len_chars = (int)strlen(msg);
    int box_x_px = (x_chars - pad_x_cells) * CELL_W;
    int box_y_px = (y_chars - pad_y_cells) * CELL_H;
    int box_w_px = (text_len_chars + 2 * pad_x_cells) * CELL_W;
    int box_h_px = (1 + 2 * pad_y_cells) * CELL_H;

    // Keep the box dark
    draw_filled_rect_px(box_x_px, box_y_px, box_w_px, box_h_px, 0x0000);

    // (Optional) seed the whole background once so you start with a full field
    #define INITIAL_FILL 1
    if (INITIAL_FILL) {
        initial_fill_soft_color_with_mask(0, box_x_px, box_y_px, box_w_px, box_h_px);
    }

    // Organic mode: update random pixels one-by-one outside the box
    uint32_t tick = 1;
    while (1) {
        // pick a random (x,y) outside the blackout box
        int x, y;
        do {
            x = (int)(xorshift32() % SCREEN_WIDTH);
            y = (int)(xorshift32() % SCREEN_HEIGHT);
        } while (x >= box_x_px && x < box_x_px + box_w_px &&
                 y >= box_y_px && y < box_y_px + box_h_px);

        // write a new soft-colored value using evolving tick
        VGA_PIXEL_BASE[y * PIXEL_STRIDE + x] = noise_color_soft565(tick, x, y);

        // advance temporal seed a bit (controls how quickly colors change)
        tick++;

        // Optional: increase update rate by doing a small burst per loop
        // for (int i = 0; i < 256; ++i) { ...same body... }
    }
    return 0;
}
