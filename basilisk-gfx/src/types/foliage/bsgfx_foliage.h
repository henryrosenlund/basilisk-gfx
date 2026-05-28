#ifndef BSGFX_FOLIAGE_H
#define BSGFX_FOLIAGE_H

#include <types/bsgfx_type.h>

//#define BSGFX_FOLIAGE_TEXTURES_COUNT 16
#define BSGFX_MAX_NUM_FOLIAGES 256

typedef struct {
	bs_GUID guid;
	int density;
	int textures_count;

	struct bsgfx_FoliageTexture {
		bs_vec4 coords;
		bs_vec2 size;
		int id;
		bs_RGBA color;
	} textures[];
} bsgfx_Foliage;

typedef struct {
	bs_GUID guid;
	int density;
	int textures_count;

	struct bsgfx_RawFoliageTexture {
		bs_U64 texture_hash;
		bs_RGBA color;
		int reserved;
	} textures[];
} bsgfx_RawFoliage;

void
bsgfx_loadFoliages(
	int package_id);

int
bsgfx_queryFoliage(
	bs_GUID* guid);

#endif