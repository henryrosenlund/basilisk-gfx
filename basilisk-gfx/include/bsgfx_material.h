#ifndef BSGFX_MATERIAL_H
#define BSGFX_MATERIAL_H

#include <bs_types.h>
#include <bs_core.h>
#include <bs_objects.h>
#include <bsgfx_scene.h>
#include <../bsgfx_contracts.h>

typedef enum {
	BSGFX_MATERIAL_CATEGORY_NONE,

	BSGFX_MATERIAL_CATEGORY_UI_COLOR_SCHEME,

	BSGFX_MATERIAL_CATEGORY_COUNT
} bsgfx_MaterialCategory;

extern const char* _bsgfx_material_categories[BSGFX_MATERIAL_CATEGORY_COUNT];

typedef struct {
	bs_U64 hash;
	char* name;
	bsgfx_MaterialCategory category;
	bool highlighted, auto_unhighlight;
	bool editable;
	int id;
	int json_index;

	bsgfx_MaterialContract* contract;
} bsgfx_Material;
extern bs_List _bsgfx_materials;

BSGFXAPI const char*
bsgfx_materialCategoryName(
	bsgfx_MaterialCategory category);

BSGFXAPI bs_List*
bsgfx_materials();

BSGFXAPI bsgfx_Material*
bsgfx_queryMaterialHash(
	bs_U64 hash);

BSGFXAPI char*
bsgfx_materialName(
	int id);

BSGFXAPI bsgfx_Material*
bsgfx_queryMaterial(
	const char* name);

BSGFXAPI bs_U64
bsgfx_materialHash(
	int id);

BSGFXAPI void 
bsgfx_allocateMaterials();

BSGFXAPI void 
bsgfx_loadMaterials();

BSGFXAPI bsgfx_Material*
bsgfx_material(
	char* name);

BSGFXAPI bsgfx_Material*
bsgfx_materialF(
	const char* format, 
	...);

/**
 These are kinda scuffed because they just brighten the color of the material -
 so calling it repeatedly will keep increasing it
 */

BSGFXAPI void
bsgfx_highlightMaterial(
	int material_id,
	bool auto_unhighlight);

BSGFXAPI void
bsgfx_unhighlightMaterial(
	int material_id);

BSGFXAPI void 
bsgfx_tickMaterials();

#endif