#include "object.h"

/**
 * Determine if the ray hits the sphere:
 */
bool hitSphere(ray r, double ray_tmin, double ray_tmax, hit_record* rec, sphere s) {
    // ray-sphere function:
    vec3* oc = malloc(sizeof(vec3));
    vec3_sub(oc, *s.center, *r.orig);

    double a = length_sqd(*r.dir);
    double h = vec3_dot(*r.dir, *oc);
    double c = (length_sqd(*oc)) - s.radius * s.radius;

    double discriminant = h*h - a*c;

    double sqrtd = sqrt(discriminant);

    double root = (h - sqrtd) / a;
    // check if the root is in the acceptable range:
    if (root <= ray_tmin || ray_tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            if (oc != NULL)
                free(oc);
            return false;
        }
    }

    // update hit record:
    rec->t = root;

    if (rec->p != NULL)
        free(rec->p);
    rec->p = at(r, rec->t);

    if (rec->normal != NULL)
        free(rec->normal);
    vec3* v = malloc(sizeof(vec3));
    vec3_sub(v, *rec->p, *s.center);
    vec3_scalar(rec->normal, *v, (1.0 / s.radius));

    if (v != NULL)
        free(v);
    if (oc != NULL)
        free(oc);

    return true;
}

void set_front_face(ray r, vec3* outward_normal, hit_record *rec) {
    rec->front_face = vec3_dot(*r.dir, *outward_normal) < 0;
    vec3* v = malloc(sizeof(vec3));
    vec3_negative(v, *outward_normal);
    if (rec->normal != NULL)
        free(rec->normal);
    rec->normal = rec->front_face ? outward_normal : v;
}