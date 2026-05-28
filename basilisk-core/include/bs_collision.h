#ifndef BS_COLLISION_H
#define BS_COLLISION_H

#include <bs_types.h>

BSAPI bs_Ray
bs_ray(
	bs_vec3 start, 
	bs_vec3 direction, 
	float length);

BSAPI bool
bs_rayVsObb(
	const bs_Ray* ray,
	bs_vec3 position, bs_vec4 rotation, bs_vec3 scale,
	bs_vec3* coordinate,
	bs_vec3* normal,
	int* plane);

BSAPI bool
bs_sphereVsPoint(
	bs_vec3 center,
	float radius,
	bs_vec3 point);

BSAPI bool
bs_sphereVsBox(
	bs_vec3 center,
	float radius,
	bs_vec3 position,
	bs_vec4 rotation,
	bs_vec3 scale,
	bs_vec3* point,
	bs_vec3* normal,
	float* penetration);

BSAPI bool
bs_rectangleVsPoint(
	bs_vec2 position, 
	bs_vec2 dimensions,
	bs_vec2 point);

BSAPI bool
bs_rectangleVsPointAbs(
	bs_vec2 position,
	bs_vec2 dimensions,
	bs_vec2 point);

BSAPI bool
bs_lineVsLine(
	bs_vec2 l1_start,
	bs_vec2 l1_end,
	bs_vec2 l2_start,
	bs_vec2 l2_end,
	bs_vec2* out);

#endif // BS_COLLISION_H