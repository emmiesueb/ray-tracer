#include "vectors.h"

/** VECTOR MATH **/

/**
 * Dot product between two vectors
 */
double vec3_dot(vec3 v, vec3 w) {
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

/**
 * Cross product between two vectors
 */
void vec3_cross(vec3 out, vec3 v, vec3 w) {
    out.x = v.y * w.z - w.y * v.z;
    out.y = w.x * v.z - v.x * w.z;
    out.z = v.x * w.y - v.y * w.x;
}

/**
 * Vector subtraction
 */
void vec3_sub(vec3 out, vec3 v, vec3 w) {
    out.x = v.x - w.x;
    out.y = v.y - w.y;
    out.z = v.z - v.z;
}

/**
 * Vector addition
 */
void vec3_add(vec3 out, vec3 v, vec3 w) {
    out.x = v.x + w.x;
    out.y = v.y + w.y;
    out.z = v.z + w.z;
}

/**
 * Multiple a vector by a scalar
 */
void vec3_scalar(vec3 out, vec3 v, double s) {
    out.x = v.x * s;
    out.y = v.y * s;
    out.z = v.z * s;
}

/**
 * Helper
 */
double length_sqd(vec3 v) {
    return v.x * v.x + v.y*v.y + v.z*v.z;
}

/**
 * Length of the vector
 */
double length(vec3 v) {
    return sqrt(length_sqd(v));
}

// aspect ratio constants
#define     X   1024
#define     Y   1024

#define     SAMPLES_PER_PIXEL   100

double image[Y][X][3];

/** TEXTURE RENDERING */

#define     TX  512
#define     TY  512

double texture[TY][TX][3];

void load_texture(void) {
    FILE *f;
    int x, y;
    unsigned char r, g, b;
    char s[256];

    // file to load texture from
    f = fopen("../Textures/Martini.ppm", "rb");
    if (!f) {
        perror("Failed to open file");
        exit(1);
    }

    fscanf(f, "%s", s); // P6
    fscanf(f, "%s", s); // 512
    fscanf(f, "%s", s); // 512
    fscanf(f, "%s", s); // 255

    for (y = 0; y < TY; y++) {
        for (x = 0; x < TX; x++) {
            // fscanf(f, "%d %d %d", &r, &g, &b);
            fread(&r, 1, 1, f);
            fread(&g, 1, 1, f);
            fread(&b, 1, 1, f);
            texture[y][x][0] = r / 255.0;
            texture[y][x][1] = g / 255.0;
            texture[y][x][2] = b / 255.0;
        }
    }
    fclose(f);

    // file to print texture to, for testing
    f = fopen("../Assets/foo.ppm", "wb");
    // printf("create file success");
    fprintf(f, "P6\n512 512\n255\n");
    for (y = 0; y < TY; y++) {
        for (x = 0; x < TX; x++) {
            fprintf(f, "%d %d %d\n", 
                (int) texture[y][x][0] * 255,
                (int) texture[y][x][1] * 255, 
                (int) texture[y][x][2] * 255);
        }
    }
    fclose(f);
}

// int main(int argc, char *argv[]) {
//     FILE *f;
//     int x, y;
//     double dx, dy;
//     struct triangle t;
//     int u, v;
//     vec3 p, uv;
//     vec3 v1, v2;
//     vec3 na, nb, nc, n;
//     vec3 bary;
//     double sx, sy;

//     load_texture();

//     // test triangle coordinates:
//     t.a[0] = -0.5;
//     t.a[1] = -0.5;
//     t.a[2] = -1.0;

//     t.b[0] = 0.0;
//     t.b[1] = 0.0;
//     t.b[2] = -1.0;

//     t.c[0] = -0.25;
//     t.c[1] = 0.5;
//     t.c[2] = -1.0;

//     // texture coordinates:
//     t.ta[0] = -0.5;
//     t.ta[1] = -0.5;
//     t.ta[2] = -1.0;

//     t.tb[0] = 0.0;
//     t.tb[1] = 0.0;
//     t.tb[2] = -1.0;

//     t.tc[0] = -0.25;
//     t.tc[1] = 0.5;
//     t.tc[2] = -1.0;

//     // n = (B-A) x (C-A)
//     vec3_sub(v1, t.b, t.a);
//     vec3_sub(v2, t.c, t.a);
//     vec3_cross(n, v1, v2);

//     // Calculating barycentric coordinates:
//     for (y = 0; y < Y; y++) {
//         for (x = 0; x < X; x++) {
//             dx = ((x - (X / 2.0)) / (X / 2.0)) + (1.0 / X);
//             dy = ((y - (Y / 2.0)) / (Y / 2.0)) + (1.0 / Y);

//             p[0] = dx;
//             p[1] = dy;
//             p[2] = -1.0;

//             // (C-B) x (P-B)
//             vec3_sub(v1, t.c, t.b);
//             vec3_sub(v2, p, t.b);
//             vec3_cross(na, v1, v2);
//             // (A-C) x (P-C)
//             vec3_sub(v1, t.a, t.c);
//             vec3_sub(v2, p, t.c);
//             vec3_cross(nb, v1, v2);
//             // (B-A) x (P-A)
//             vec3_sub(v1, t.b, t.a);
//             vec3_sub(v2, p, t.a);
//             vec3_cross(nc, v1, v2);

//             bary[0] = vec3_dot(n, na) / vec3_dot(n, n);
//             bary[1] = vec3_dot(n, nb) / vec3_dot(n, n);
//             bary[2] = vec3_dot(n, nc) / vec3_dot(n, n);

//             // Texture coordinate calculations
//             vec3_sub(v1, t.tb, t.ta);
//             vec3_scalar(v1, v1, bary[1]);
//             vec3_sub(v2, t.tc, t.ta);
//             vec3_scalar(v2, v2, bary[2]);
//             vec3_add(uv, v1, v2);
//             vec3_add(uv, t.ta, uv);

//             // image[y][x][0] += bary[0];
//             // image[y][x][1] += bary[1];
//             // image[x][y][2] += bary[2];
//             if (bary[0] >= 0 && bary[1] >= 0 && bary[2] >= 0) {
//                 u = (int) (uv[0] * TX);
//                 v = (int) (uv[1] * TY);
//                 image[y][x][0] = texture[v][u][0];
//                 image[y][x][1] = texture[v][u][1];
//                 image[y][x][2] = texture[v][u][2];
//             }
//         }
//     }

//     f = fopen("barycentric.ppm", "wb");
//     fprintf(f, "P3\n%d\n%d\n255\n", X, Y);
//     for (y = Y-1; y >= 0; y--) {
//         for (x = 0; x < X; x++) {
//             fprintf(f, "%d %d %d\n",
//                 (unsigned char) image[y][x][0] * 255.99 / SAMPLES_PER_PIXEL,
//                 (unsigned char) image[y][x][1] * 255.99 / SAMPLES_PER_PIXEL,
//                 (unsigned char) image[y][x][2] * 255.99 / SAMPLES_PER_PIXEL);
//         }
//     }
//     fclose(f);

//     return 0;
// }