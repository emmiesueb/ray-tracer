#include "ray.h"

/**
 * Compute a point along the ray
 */
point3* at(ray r, double t) {
    point3* p = malloc(sizeof(point3));
    p->x = r.orig->x + t * r.dir->x;
    p->y = r.orig->y + t * r.dir->y;
    p->z = r.orig->z + t * r.dir->z;
    return p;
}