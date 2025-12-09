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
 * Unit vector
 */
void vec3_unit(vec3 out, vec3 v) {
    vec3_scalar(out, v, (1.0 / vec3_length(v)));
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
double vec3_length(vec3 v) {
    return sqrt(length_sqd(v));
}