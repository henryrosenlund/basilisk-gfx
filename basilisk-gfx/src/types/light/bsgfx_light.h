#ifndef BSGFX_LIGHT_H
#define BSGFX_LIGHT_H

#include <bs_types.h>
#include <../bsgfx_contracts.h>

#define BSGFX_LIGHT_VERSION 2

typedef enum {
	BSGFX_LIGHT_TYPE_POINT = 1,
	BSGFX_LIGHT_TYPE_SUN = 2,
} bsgfx_LightType;

typedef struct {
	bs_vec3 position;
	bs_vec3 direction;
	bsgfx_LightType type;
} bsgfx_Light;

typedef struct {
	bs_vec3 position;
	bs_vec3 rotation;
	bsgfx_LightType type;
	int reserved_a;
	int reserved_b;
	int reserved_c;
	int reserved_d;
	int reserved_e;
} bsgfx_RawLight;

BSGFXAPI void 
bsgfx_loadLights(
	int package_id);

#endif