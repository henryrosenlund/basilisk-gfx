#ifndef BSGFX_ENTITY_H
#define BSGFX_ENTITY_H

#include <bs_types.h>
#include <types/spawner/bsgfx_spawner.h>

typedef enum bsgfx_Id bsgfx_Id;

typedef enum {
	BSGFX_COMPONENT_MODEL,
	BSGFX_COMPONENT_ARMATURE,
	BSGFX_COMPONENT_COLLIDER,
	BSGFX_COMPONENT_CONTROLLER,
	BSGFX_COMPONENT_ANIMATOR,
	BSGFX_COMPONENT_EQUIPMENT,

	BSGFX_COMPONENT_COUNT
} bsgfx_ComponentType;

/*
typedef struct {
	int mesh_id;
} bsgfx_EntityItem;

typedef struct {
	bsgfx_EntityModel* model;
	bsgfx_EntityArmature* armature;
	bsgfx_EntityAnimator* animator;
	bsgfx_EntityCollider* collider;
	bsgfx_EntityController* controller;
	bsgfx_EntityEquipment* equipment;

	int id;
	bs_List inventory;
	bsgfx_Script* script;
} bsgfx_Entity;

#define BSGFX_COMPONENT(e, name) [e] = { \
	.enum_name = #e, \
	.names = bsgfx_entity_##name##_names, \
	.sizes = bsgfx_entity_##name##_sizes, \
	.count = &bsgfx_entity_##name##_count, \
	.types = &bsgfx_entity_##name##_lua_types, \
	.offset = offsetof(bsgfx_Entity, name), \
	.size = sizeof(*((bsgfx_Entity *)NULL)->##name##), \
	.field_name = #name \
}

static const struct {
	const char* enum_name;
	const char* field_name;
	const char** names;
	const size_t* sizes;
	const size_t size;
	const int* count;
	const bsgfx_LuaType* types;
	const size_t vk_offset;
} bsgfx_components[BSGFX_COMPONENT_COUNT] = {
	BSGFX_COMPONENT(BSGFX_COMPONENT_MODEL, model),
	BSGFX_COMPONENT(BSGFX_COMPONENT_ARMATURE, armature),
	BSGFX_COMPONENT(BSGFX_COMPONENT_COLLIDER, collider),
	BSGFX_COMPONENT(BSGFX_COMPONENT_CONTROLLER, controller),
	BSGFX_COMPONENT(BSGFX_COMPONENT_ANIMATOR, animator),
	BSGFX_COMPONENT(BSGFX_COMPONENT_EQUIPMENT, equipment),
};

//#define BSGFX_TYPE(type, capacity, plural, singular, t1, t2) \
//    bsgfx_type(type, #plural, #singular, &bsgfx_##plural##_capacity, &bsgfx_##plural##_count, sizeof(t1)); \
//    bsgfx_##plural = bs_realloc(bsgfx_##plural, bsgfx_##plural##_capacity * sizeof(t2));



//#define BSGFX_TYPE_FORMAT(type, capacity, plural, singular, mapper, t, flexible) \
//	bsgfx_type(\
//		type,\
//		#plural,\
//		#singular,\
//		&bsgfx_##plural##_capacity,\
//		&bsgfx_##plural##_count,\
//        sizeof(struct { BSGFX_TYPE_FIELDS(BSGFX_TYPE_STRUCTURE) }), \
//		sizeof(t), \
//        (const char* []) { BSGFX_TYPE_FIELDS(BSGFX_TYPE_FIELD_NAMES) }, \
//        (const char* []) { BSGFX_TYPE_FIELDS(BSGFX_TYPE_NAMES) }, \
//        (size_t[]) { BSGFX_TYPE_FIELDS(BSGFX_TYPE_SIZES) },\
//		mapper,\
//		flexible);


extern bs_List bsgfx_entities;

BSGFXAPI void bsgfx_readEntityComponents(bsgfx_Entity* entity);
BSGFXAPI void bsgfx_saveEntityComponents(bsgfx_Entity* entity);

BSGFXAPI void bsgfx_readEntityComponent(bsgfx_Entity* entity, int component_id);
BSGFXAPI void bsgfx_saveEntityComponent(bsgfx_Entity* entity, int component_id);

BSGFXAPI void bsgfx_tickEntities();
BSGFXAPI void bsgfx_fixedTickEntities();
BSGFXAPI void bsgfx_spawnEntity(bsgfx_Script* script, bs_vec3 position);
BSGFXAPI void bsgfx_appendInventory(int entity_id, int item_id);
BSGFXAPI void bsgfx_entityFromInventory(const char* script_name, int entity_id, int inventory_id);
BSGFXAPI void bsgfx_respawnScriptEntities(bsgfx_Script* script);

*/

#endif