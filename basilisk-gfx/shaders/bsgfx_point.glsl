#ifndef BSGFX_POINT_GLSL
#define BSGFX_POINT_GLSL

#include "../../../basilisk-gfx/bsgfx_contracts.h"

struct bsgfx_PointInstance {
    bsgfx_InstanceHeader header;
    vec3 coord;
    float size;
    vec4 color;
    vec4 a, b;
};

layout(set = BSGFX_SET_POINT_INSTANCES, binding = BSGFX_BINDING_POINT_INSTANCES) readonly uniform bsgfx_point_instance_uniform {
    bsgfx_PointInstance bsgfx_point_instances[BSGFX_POINT_INSTANCE_COUNT];
};

float bsgfx_pointSize(uint instance) {
    return bsgfx_point_instances[instance].size;
}

vec4 bsgfx_translatePoint(uint instance) {
    return vec4(bsgfx_point_instances[instance].coord.xyz, 1.0);
}

#endif