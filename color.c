#include "color.h"

/**
 * Write a single pixel's color to the console output:
 */
const char* write_color(char* restrict line, color pixel_color) {
    double r = pixel_color.x;
    double g = pixel_color.y;
    double b = pixel_color.z;

    int rbyte = (int) (r * 255.99);
    int gbyte = (int) (g * 255.99);
    int bbyte = (int) (b * 255.99);

    sprintf(line, "%d %d %d\n", rbyte, gbyte, bbyte);
    return line;
}