#ifndef BSGFX_PRIMITIVE_H
#define BSGFX_PRIMITIVE_H

#include <types/bsgfx_type.h>

#define BSGFX_MAX_PRIMITIVES_COUNT					(512)
#define BSGFX_PRIMITIVE_VERSION						1

typedef bs_U32 bsgfx_PrimitiveFlags;
typedef enum {
	BSGFX_PRIMITIVE_HIDDEN = 1 << 0,
} bsgfx_PrimitiveFlag;

typedef enum {
	BSGFX_PRIMITIVE_TYPE_BOX,
	BSGFX_PRIMITIVE_TYPE_SPHERE,

	BSGFX_PRIMITIVE_TYPE_COUNT,
} bsgfx_PrimitiveType;

typedef struct {
	bs_vec3 position;
	bs_vec4 rotation;
	bs_vec3 scale;

	int first_tile, last_tile;

	bs_U32 collision;
	bsgfx_PrimitiveFlags flags;
	bsgfx_PrimitiveType type;
	int subtype_index;

	bs_GUID guid;
} bsgfx_Primitive;

typedef struct {
	bs_vec3 position;
	bs_vec3 scale;
	bs_vec3 rotation;

	bs_U32 collision;
	bsgfx_PrimitiveFlags flags;
	bsgfx_PrimitiveType type;

	bs_GUID guid;
} bsgfx_RawPrimitive;

typedef struct {
	bs_vec3 normal;
	bs_vec3 right;
	bs_vec3 up;
	bs_vec3 start_sign;
	int width_axis;
	int height_axis;
} bsgfx_TileAxis;

BSGFXAPI bs_vec3
bsgfx_primitivePosition(
	bsgfx_RawPrimitive* primitive);

BSGFXAPI void
bsgfx_loadPrimitives(
	int package_id);

BSGFXAPI int
bsgfx_primitiveSubtype(
	bsgfx_PrimitiveType type);

BSGFXAPI int
bsgfx_instancePrimitive(
	int subtype,
	bs_mat4 transform,
	bs_U32 flags,
	int id,
	int material);

BSGFXAPI int 
bsgfx_queryTilePrimitive(
	int tile_id);

BSGFXAPI void
bsgfx_instancePrimitives();

BSGFXAPI void
bsgfx_renderPrimitives(
	bs_mat4 camera);

BSGFXAPI int
bsgfx_queryPrimitive(
	bs_GUID* guid);

#endif