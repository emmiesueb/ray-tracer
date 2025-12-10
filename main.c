#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "camera.h"
#include "object.h"
#include "texture-load.h"

#define frand() (rand() / (RAND_MAX + 1.0))

// ASPECT RATIO

#define     SAMPLES_PER_PIXEL   100

int main() {
    FILE *f;

    // Camera
    camera *c = malloc(sizeof(camera));
    initialize(c);

    // Render
    f = fopen("image.ppm", "wb");
    fprintf(f, "P3\n%d\n%d\n255\n", c->image_width, c->image_height);


        for (int j = 0; j < c->image_height; j++) {
            for (int i = 0; i < c->image_width; i++) {
                // pixel center:
                vec3 v1, v2, r1, pixel_center;
                vec3_scalar(&v1, *c->pixel_delta_u, (double) i);
                vec3_scalar(&v2, *c->pixel_delta_v, (double) j);
                vec3_add(&r1, v1, v2);
                vec3_add(&pixel_center, *c->pixel00_loc, r1);
                
                // ray direction:
                vec3* ray_dir = malloc(sizeof(vec3));
                vec3_sub(ray_dir, pixel_center, *c->center);

                // initialize the ray:
                ray r;
                r.orig = c->center;
                r.dir = ray_dir;
                free(ray_dir);

                color pixel_color = ray_color(r);
                char* restrict line = malloc(sizeof(const char*) * 20);
                write_color(line, pixel_color);
                fprintf(f, "%s", line);
                free(line);
            }
        }

    fclose(f);

    return 0;
}