#include <stdint.h>

#define WIDTH 640 
#define HEIGHT 480

uint32_t pixel_buffer[WIDTH * HEIGHT];

uint32_t* get_buffer_pointer() {
    return pixel_buffer;
}

void generate_frame(int frame_count) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            uint8_t r = (x + frame_count) % 255;
            uint8_t g = (y + frame_count) % 255;
            uint8_t b = 128;
            uint8_t a = 255;

            pixel_buffer[y * WIDTH + x] = (a << 24) | (b << 16) | (g << 8) | r;
        }
    }
}

