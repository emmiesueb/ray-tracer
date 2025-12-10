#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "vectors.h"
#include "ray.h"
#include "color.h"
#include "camera.h"
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
                vec3 v1 = vec3_scalar(c->pixel_delta_u, (double) i);
                vec3 v2 = vec3_scalar(c->pixel_delta_v, (double) j);
                vec3 r1 = vec3_add(v1, v2);
                vec3 pixel_center = vec3_add(c->pixel100_loc, r1);
                
                // ray direction:
                vec3 ray_direction = vec3_sub(pixel_center, c->center);

                // initialize the ray:
                ray r;
                r.orig = c->center;
                r.dir = ray_direction;

                color pixel_color = ray_color(r);
                char* restrict line = malloc(sizeof(const char*) * 20);
                write_color(line, pixel_color);
                fprintf(f, "%s", line);
            }
        }

    fclose(f);

    return 0;
}

// commented out, not helpful for testing right now
// int main() {
//     FILE *f;
//     int x, y;
//     double dx, dy;
//     triangle t;
//     int u, v;
//     vec3 p, uv;
//     vec3 v1, v2;
//     vec3 na, nb, nc, n;
//     vec3 bary;
//     double sx, sy;
//     int s;

//     load_texture(texture);

//     // test triangle coordinates:
//     t.a.x = -0.5;
//     t.a.y = -0.5;
//     t.a.z = -1.0;

//     t.b.x = 0.0;
//     t.b.y = 0.0;
//     t.b.z = -1.0;

//     t.c.x = -0.25;
//     t.c.y = 0.5;
//     t.c.z = -1.0;

//     // texture coordinates:
//     t.ta.x = -0.5;
//     t.ta.y = -0.5;
//     t.ta.z = -1.0;

//     t.tb.x = 0.0;
//     t.tb.y = 0.0;
//     t.tb.z = -1.0;

//     t.tc.x = -0.25;
//     t.tc.y = 0.5;
//     t.tc.z = -1.0;

//     // n = (B-A) x (C-A)
//     vec3_sub(v1, t.b, t.a);
//     vec3_sub(v2, t.c, t.a);
//     vec3_cross(n, v1, v2);

//     // Calculating barycentric coordinates:
//     for (y = 0; y < Y; y++) {
//         for (x = 0; x < X; x++) {
//             // anti-aliasing loop:
//             for (s = 0; s < SAMPLES_PER_PIXEL; s++) {
//                 sx = (frand() / X) - (1.0 / (2.0 * X));
//                 sy = (frand() / Y) - (1.0 / (2.0 * Y));

//                 dx = ((x - (X / 2.0)) / (X / 2.0)) + (1.0 / X) + sx;
//                 dy = ((y - (Y / 2.0)) / (Y / 2.0)) + (1.0 / Y) + sy;

//                 p.x = dx;
//                 p.y = dy;
//                 p.z = -1.0;

//                 // (C-B) x (P-B)
//                 vec3_sub(v1, t.c, t.b);
//                 vec3_sub(v2, p, t.b);
//                 vec3_cross(na, v1, v2);
//                 // (A-C) x (P-C)
//                 vec3_sub(v1, t.a, t.c);
//                 vec3_sub(v2, p, t.c);
//                 vec3_cross(nb, v1, v2);
//                 // (B-A) x (P-A)
//                 vec3_sub(v1, t.b, t.a);
//                 vec3_sub(v2, p, t.a);
//                 vec3_cross(nc, v1, v2);

//                 bary.x = vec3_dot(n, na) / vec3_dot(n, n);
//                 bary.y = vec3_dot(n, nb) / vec3_dot(n, n);
//                 bary.z = vec3_dot(n, nc) / vec3_dot(n, n);

//                 // Texture coordinate calculations
//                 vec3_sub(v1, t.tb, t.ta);
//                 vec3_scalar(v1, v1, bary.y);
//                 vec3_sub(v2, t.tc, t.ta);
//                 vec3_scalar(v2, v2, bary.z);
//                 vec3_add(uv, v1, v2);
//                 vec3_add(uv, t.ta, uv);

//                 if (bary.x >= 0 && bary.y >= 0 && bary.z >= 0) {
//                     u = (int) (uv.x * TX);
//                     v = (int) (uv.y * TY);
//                     if (u >= 0 && u < TX && v >= 0 && v < TY) {
//                         image[y][x][0] += texture[v][u][0];
//                         image[y][x][1] += texture[v][u][1];
//                         image[y][x][2] += texture[v][u][2];
//                     }
//                 }
//             }
//         }
//     }

//     // writing image:
//     f = fopen("barycentric.ppm", "wb");
//     fprintf(f, "P3\n%d\n%d\n255\n", X, Y);
//     for (y = Y-1; y >= 0; y--) {
//         for (x = 0; x < X; x++) {
//             fprintf(f, "%d %d %d\n",
//                 (unsigned char) (image[y][x][0] * 255.99 / SAMPLES_PER_PIXEL),
//                 (unsigned char) (image[y][x][1] * 255.99 / SAMPLES_PER_PIXEL),
//                 (unsigned char) (image[y][x][2] * 255.99 / SAMPLES_PER_PIXEL));
//         }
//     }
//     fclose(f);

//     return 0;
// }
