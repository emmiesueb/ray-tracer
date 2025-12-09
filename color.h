#ifndef COLOR_H
#define COLOR_H

#include <stdlib.h>

#include "vectors.h"
#include "ray.h"

typedef vec3 color;

void write_color(color);

color ray_color(ray);

#endif