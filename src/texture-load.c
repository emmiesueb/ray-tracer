#include "texture-load.h"

void load_texture(double texture[TY][TX][3]) {
    FILE *f;
    int x, y;
    unsigned char r, g, b;
    char s[256];

    // file to load texture from
    f = fopen("./Textures/Martini.ppm", "rb");
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
    fprintf(f, "P6\n512\n512\n255\n");
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