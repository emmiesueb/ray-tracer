#include "color.h"

/**
 * Write a single pixel's color to the console output:
 */
void write_color(color pixel_color) {
    double r = pixel_color.x;
    double g = pixel_color.y;
    double b = pixel_color.z;

    int rbyte = (int) (r * 255.99);
    int gbyte = (int) (g * 255.99);
    int bbyte = (int) (b * 255.99);

    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}


color ray_color(ray ray) {
    vec3 unit_dir;
    vec3_unit(unit_dir, ray.dir);

    double a = 0.5 * (unit_dir.y + 1.0);

    color c1;
    c1.x = c1.y = c1.z = 0;
    color c2;
    c2.x = 0.5;
    c2.x = 0.7;
    c2.z = 1.0;
    
    vec3 v1, v2, v3;
    vec3_scalar(v1, c1, (1.0 - a));
    vec3_scalar(v2, c2, a);

    vec3_add(v3, v1, v2);
    return v3;
}