#ifndef BSGFX_PREFAB_H
#define BSGFX_PREFAB_H

#include <types/bsgfx_type.h>

#define BSGFX_MAX_NUM_PREFABS 512
#define BSGFX_PREFAB_VERSION 1

enum {
	BSGFX_PREFAB_SUBTYPE_PRIMITIVE,
};

typedef enum {
	BSGFX_PREFAB_SUBTYPE_MESH,
	BSGFX_PREFAB_SUBTYPE_MESH_POLYGON_OUTLINE,
	BSGFX_PREFAB_SUBTYPE_MESH_TEXTURED,
	BSGFX_PREFAB_SUBTYPE_MESH_HI_RES_SCREEN,
	BSGFX_PREFAB_SUBTYPE_MESH_LO_RES_SCREEN,
	BSGFX_PREFAB_SUBTYPE_MESH_VOLUME,

	BSGFX_PREFAB_SUBTYPE_COUNT,
} bsgfx_PrefabSubtype;

enum {
	BSGFX_PREFAB_HAS_COLLIDER = 1 << 0,
	BSGFX_PREFAB_HIDDEN = 1 << 1,
	BSGFX_PREFAB_TEXTURED_SHADOWS = 1 << 2,
	BSGFX_PREFAB_NO_DEPTH = 1 << 3,
	BSGFX_PREFAB_WRITE_POSITION = 1 << 4,
};

typedef struct bsgfx_PrefabVariety bsgfx_PrefabVariety;
typedef struct bsgfx_PrefabMetadata bsgfx_PrefabMetadata;
extern struct bsgfx_PrefabMetadata {
	int variety_count;
	struct bsgfx_PrefabVariety {
		int texture_id;
	}*varieties;
}*bsgfx_prefabs;
extern int bsgfx_prefabs_count;

typedef struct {
	bs_vec3 position;
	bs_vec4 rotation;
	bs_vec3 scale;
	int mesh_id;
	int material_id;
	int texture_id;
	int z_order;
	bs_U32 flags;
	int shadow_subtype;
	bs_GUID guid;
} bsgfx_Prefab;

typedef struct {
	bs_vec3 position;
	bs_vec3 rotation;
	bs_vec3 scale;
	bs_U32 flags;
	bs_U64 name_hash;
	bs_U64 material_hash;
	bs_U64 texture_hash;
	bs_GUID guid;
	int z_order;
	int reserved;
} bsgfx_RawPrefab;

BSGFXAPI void bsgfx_computePrefabShadows();
BSGFXAPI void bsgfx_renderPrefabShadowVolumes();

BSGFXAPI bsgfx_PrefabMetadata*
bsgfx_prefabMetadata(
	int mesh_id);

BSGFXAPI void
bsgfx_savePrefabs();

BSGFXAPI void
bsgfx_loadPrefabs(
	int package_id,
	bs_Model* model);

BSGFXAPI bs_mat4
bsgfx_prefabTransform(
	bsgfx_Prefab* prefab);

BSGFXAPI int 
bsgfx_instancePrefabModel(
	int mesh_id, 
	bs_mat4 transform, 
	bsgfx_PrefabSubtype prefab_subtype, 
	int material_id);

BSGFXAPI int 
bsgfx_instancePrefab(
	int id, 
	bsgfx_PrefabSubtype prefab_subtype);

BSGFXAPI void
bsgfx_instancePrefabs();

BSGFXAPI void
bsgfx_renderPrefabs(
	bs_Pipeline* pipeline,
	int key_start);

BSGFXAPI void 
bsgfx_renderScenePrefabs();

BSGFXAPI void 
bsgfx_renderPrefabPrimitives(
	bs_Pipeline* pipeline, 
	int key_start);

BSGFXAPI bsgfx_RawPrefab*
bsgfx_tilePrefab(
	bs_vec2 coords);

BSGFXAPI int
bsgfx_queryPrefabId(
	const bs_GUID* guid);

BSGFXAPI int
bsgfx_closestPrefab(
	bs_U64 mesh_name_hash,
	bs_vec3 position,
	float radius);

#endif