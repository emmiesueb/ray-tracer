#include "camera.h"

/**
 * Initialize the camera:
 */
void initialize(camera *c) {
    c->aspect_ratio = 16.0 / 9.0;
    c->image_width = 400;
    c->image_height = (int) (c->image_width / c->aspect_ratio);
    c->image_height = (c->image_height < 1) ? 1 : c->image_height;

    c->center.x = c->center.y = c->center.z = 0;

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double) (c->image_width) / c->image_height);

    // calculate the vectors across the horizontal and down the vertical viewport edges:
    vec3 viewport_u, viewport_v;
    viewport_u.y = viewport_u.z = viewport_v.x = viewport_v.z = 0;
    viewport_u.x = viewport_width;
    viewport_v.y = -viewport_height;

    // calculate horizontal and vertical delta vectors from pixel to pixel:
    c->pixel_delta_u = vec3_scalar(viewport_u, (1.0 / (double) c->image_width));
    c->pixel_delta_v = vec3_scalar(viewport_v, (1.0 / (double) c->image_width));

    // find location of upper left pixel of the viewport:
    vec3 v1;
    v1.x = v1.y = 0;
    v1.z = focal_length;

    vec3 r1 = vec3_sub(c->center, v1);
    vec3 v2 = vec3_scalar(viewport_u, 0.5);

    vec3 v3 = vec3_scalar(viewport_v, 0.5);
    vec3 r2 = vec3_sub(v2, v3);

    vec3 viewport_upper_left = vec3_sub(r1, r2);
    
    vec3 v4 = vec3_add(c->pixel_delta_u, c->pixel_delta_v);
    vec3 r3 = vec3_scalar(v4, 0.5);
    c->pixel100_loc = vec3_add(viewport_upper_left, r3);
}

/**
 * Determine the color vector of the ray:
 * (currently makes the ray a blue-white gradient)
 */
color ray_color(ray ray) {
    vec3 unit_dir = vec3_unit(ray.dir);

    double a = 0.5 * (unit_dir.y + 1.0);

    color c1;
    c1.x = c1.y = c1.z = 1.0;
    color c2;
    c2.x = 0.5;
    c2.y = 0.7;
    c2.z = 1.0;

    vec3 v1 = vec3_scalar(c1, (1.0 - a));
    vec3 v2 = vec3_scalar(c2, a);

    return vec3_add(v1, v2);
}