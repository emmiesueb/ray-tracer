#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
    double z;
} vec3;

typedef vec3 point3;

typedef struct {
    vec3 a, b, c;
    vec3 ta, tb, tc;
    vec3 n;
} triangle;

double vec3_dot(vec3, vec3);

void vec3_cross(vec3, vec3, vec3);

void vec3_sub(vec3, vec3, vec3);

void vec3_add(vec3, vec3, vec3);

void vec3_scalar(vec3, vec3, double);

double x(vec3);

double y(vec3);

double z(vec3);