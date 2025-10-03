#include <std.int>
#include <std.lib>
#include <stdio.h>

/** VECTOR MATH **/
typedef double vec3[3];

double vec3_dot(vec3 u, vec3 w) {
    return v[0] * w[0] + v[1] * w[1] + v[2] * w[2];
}

void vec3_cross(vec3 out, vec3 v, vec3 w) {
    out[0] = v[1] * w[2] - w[1] * v[2];
    out[1] = w[0] * v[2] - v[0] * w[2];
    out[2] = v[0] * w[1] - v[1] * w[0];
}

void vec3_sub(vec3 out, vec3 v, vec3 w) {
    out[0] = v[0] - w[0];
    out[1] = v[1] - w[1];
    out[2] = v[2] - v[2];
}

void vec3_add(vec3 out, vec3 v, vec3 w) {
    out[0] = v[0] + w[0];
    out[1] = v[1] + w[1];
    out[2] = v[2] + w[2];
}

void vec3_scalar(vec3 out, vec3 v, double s) {
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
}

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
    int r, g, b;

    // file to load texture from
    f = fopen("../Textures/Martini.ppm", "rb");

    fscanf(f, "%s", s); // P3
    fscanf(f, "%s", s); // 1300
    fscanf(f, "%s", s); // 827
    fscanf(f, "%s", s); // 255

    for (y = 0; y < TY; y++) {
        for (x = 0; x < TX; x++) {
            fscanf(f, "%d %d %d", &r, &g, &b);
            texture[y][x][0] = r / 255.0;
            texture[y][x][1] = g / 255.0;
            texture[y][x][2] = b / 255.0;
        }
    }
    fclose(f);

    // file to print texture to, for testing
    f = fopen("foo.ppm", "wb");
    fprintf("P3\n1300 827\n255");
    for (y = 0; y < TY; y++) {
        for (x = 0; x < TX; x++) {
            fprintf(f, "%d %d %d", 
                (int) texture[y][x][0] * 255,
                (int) texture[y][x][1] * 255, 
                (int) texture[y][x][2] * 255);
        }
    }
    fclose(f);
}

struct triangle {
    vec3 a, b, c;
    vec3 ta, tb, tc;
    vec3 n;
} triangle_t;

int main(int argc, char *argv[]) {
    FILE *f;
    int x, y;
    double dx, dy;
    triangle_t t;
    vec3 p, uv;
    vec3 v1, v2;
    vec3 na, nb, nc, n;
    vec3 bary;
    double sx, sy;

    // Calculating barycentric coordinates:
    for (y = 0; y < Y; y++) {
        for (x = 0; x < X; x++) {
            dx = ((x - (X / 2.0)) / (X / 2.0)) + (1.0 / X);
            dy = ((y - (Y / 2.0)) / (Y / 2.0)) + (1.0 / Y);

            p[0] = dx;
            p[1] = dy;
            p[2] = -1.0;

            // (C-B) x (P-B)
            vec3_sub(v1, t.c, t.b);
            vec3_sub(v2, p, t.b);
            vec3_cross(na, v1, v2);
            // (A-C) x (P-C)
            vec3_sub(v1, t.a, t.c);
            vec3_sub(v2, p, t.c);
            vec3_cross(nb, v1, v2);
            // (B-A) x (P-A)
            vec3_sub(v1, t.b, t.a);
            vec3_sub(v2, p, t.a);
            vec3_cross(nc, v1, v2);
            // (B-A) x (C-A)
            vec3_sub(v1, t.b, t.a);
            vec3_sub(v2, t.c, t.a);
            vec3_cross(n, v1, v2);

            bary[0] = vec3_dot(n, na) / vec3_dot(n, n);
            bary[1] = vec3_dot(n, nb) / vec3_dot(n, n);
            bary[3] = vec3_dot(n, nc) / vec3_dot(n, n);

            // Texture coordinate calculations
            vec3_sub(v1, t.tb, t.ta);
            vec3_mul_scalar(v1, v1, bary[1]);
            vec3_sub(v2, t.tc, t.ta);
            vec3_mul_scalar(v2, v2, bary[2]);
            vec3_add(uv, v1, v2);
            vec3_add(uv, t.ta, uv);

            // image[y][x][0] += bary[0];
            // image[y][x][1] += bary[1];
            // image[x][y][2] += bary[2];
            if (bary[0] >= 0 && bary[1] >= 0 && bary[2] >= 0) {
                u = (int) (uv[0] * TX);
                v = (int) (uv[1] * TY);
                image[y][x][0] = texture[v][u][0];
                image[y][x][1] = texture[v][u][1];
                image[y][x][2] = texture[v][u][2];
            }
        }
    }

    f = fopen("barycentric.ppm", "wb");
    fprintf(f, "P3\n%d\n%d\n255\n", X, Y);
    for (y = Y-1; y >= 0; y--) {
        for (x = 0; x < X; x++) {
            fprintf(f, "%d %d %d\n",
                (unsigned char) image[y][x][0] * 255.99,
                (unsigned char) image[y][x][1] * 255.99,
                (unsigned char) image[y][x][2] * 255.99);
        }
    }

}