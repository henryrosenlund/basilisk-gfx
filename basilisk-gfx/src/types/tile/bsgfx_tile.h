#ifndef BSGFX_TILE_H
#define BSGFX_TILE_H

#include <types/bsgfx_type.h>
#include <types/primitive/bsgfx_primitive.h>

#define BSGFX_MAX_TILES_COUNT 8192
#define BSGFX_MAX_TILE_PATH_LENGTH 16

#define BSGFX_TILE_VERSION 2

typedef struct {
	bs_ivec2 coords;
	bs_U32 axis;
	int index;
	int image_index;
	bs_U32 flags;
	int material;
} bsgfx_Tile;

typedef struct {
	bs_ivec2 coords;
	bs_U32 axis;
	bs_U32 flags;
	bs_U64 texture_hash;
	bs_GUID primitive;
} bsgfx_RawTile;

typedef struct bsgfx_TileType bsgfx_TileType;
extern struct bsgfx_TileType {
	int id;
	//bs_RGBA color; // preview color for minimap
	//bs_U64 texture_hash;
};

 /**
  Outdated versions
  */
typedef struct {
	bs_vec2 coords;
	bs_U32 flags;
	bs_U64 texture_hash;
	bs_GUID primitive;
} bsgfx_RawTileV1;

BSGFXAPI void
bsgfx_loadTiles(
	int package_id,
	bool force_destroy);

void
bsgfx_instanceTiles();

BSGFXAPI bs_Range
bsgfx_pushTile(
	bs_Batch* batch,
	bs_Quad quad,
	bs_vec3 normal,
	bs_U32 index,
	int image_index);

BSGFXAPI void
bsgfx_batchTile(
	bs_Batch* batch,
	bs_U32* offset,
	bs_Quad quad,
	bs_vec3 normal,
	bs_U32 index,
	int image_index);

BSGFXAPI const bsgfx_TileAxis*
bsgfx_tileAxes();

BSGFXAPI bs_vec3
bsgfx_tilePosition(
	bsgfx_Primitive* primitive,
	int axis,
	int x,
	int y);

BSGFXAPI bs_vec4
bsgfx_tileRotation(
	int axis);

BSGFXAPI bs_vec3
bsgfx_tileEulerRotation(
	int axis);

BSGFXAPI bs_U32 bsgfx_pushTileAt(
	bs_Batch* batch,
	bsgfx_Primitive* primitive,
	int axis,
	int x,
	int y,
	bs_U32 index,
	int image_index);

BSGFXAPI bs_ivec2
bsgfx_tileCoordinate(
	bsgfx_Primitive* primitive,
	int axis,
	int index);

BSGFXAPI int
bsgfx_tileAxis(
	bsgfx_Primitive* primitive,
	int index);

BSGFXAPI bs_U32
bsgfx_tileIndex(
	bsgfx_Primitive* primitive,
	int axis,
	int x,
	int y);

#endif