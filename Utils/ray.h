#include "vectors.h"

typedef struct {
    point3 orig;
    vec3 dir;
} ray;

point3 at(ray, double);