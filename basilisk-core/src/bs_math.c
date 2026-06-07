#include <basilisk.h>
#include <cglm/vec2.h>
#include <cglm/vec3.h>
#include <cglm/vec4.h>

void bs_v2Add(bs_vec2* a, bs_vec2* b, bs_vec2* out) {
	glm_vec2_add(a->a, b->a, out->a);
}

void bs_v3Add(bs_vec3* a, bs_vec3* b, bs_vec3* out) {
	glm_vec3_add(a->a, b->a, out->a);
}

void bs_v4Add(bs_vec4* a, bs_vec4* b, bs_vec4* out) {
	glm_vec4_add(a->a, b->a, out->a);
}
