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
vec3 vec3_cross(vec3 v, vec3 w) {
    vec3 out;
    out.x = v.y * w.z - w.y * v.z;
    out.y = w.x * v.z - v.x * w.z;
    out.z = v.x * w.y - v.y * w.x;
    return out;
}

/**
 * Vector subtraction
 */
vec3 vec3_sub(vec3 v, vec3 w) {
    vec3 out;
    out.x = v.x - w.x;
    out.y = v.y - w.y;
    out.z = v.z - v.z;
    return out;
}

/**
 * Vector addition
 */
vec3 vec3_add(vec3 v, vec3 w) {
    vec3 out;
    out.x = v.x + w.x;
    out.y = v.y + w.y;
    out.z = v.z + w.z;
    return out;
}

/**
 * Multiple a vector by a scalar
 */
vec3 vec3_scalar(vec3 v, double s) {
    vec3 out;
    out.x = v.x * s;
    out.y = v.y * s;
    out.z = v.z * s;
    return out;
}

/**
 * Unit vector
 */
vec3 vec3_unit(vec3 v) {
    return vec3_scalar(v, (1.0 / vec3_length(v)));
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