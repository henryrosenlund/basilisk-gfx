#ifndef BSGFX_SPAWNER_H
#define BSGFX_SPAWNER_H

#include <types/bsgfx_type.h>

#define BSGFX_SPAWNER_VERSION 1

typedef enum {
	BSGFX_SPAWNER_ITEM,
	BSGFX_SPAWNER_ENTITY,
} bsgfx_SpawnerType;

typedef bs_U32 bsgfx_SpawnerFlags;
typedef enum {
	BSGFX_SPAWN_ON_SCENE_LOAD = 1 << 0,
};

typedef struct {
	bs_vec3 position;
	bsgfx_SpawnerType spawn_type;
	bs_U64 spawn_name;
	bsgfx_SpawnerFlags flags;
	float spawn_periodicity;
	int material_id;
	int reserved;
} bsgfx_Spawner;

typedef struct {
	bs_vec3 position;
	bsgfx_SpawnerType spawn_type;
	bs_U64 spawn_name;
	bsgfx_SpawnerFlags flags;
	float spawn_periodicity;
	bs_U64 material_name;
} bsgfx_RawSpawner;

void
bsgfx_loadSpawners(
	int package_id);

void 
bsgfx_spawn(
	bsgfx_Spawner* spawner);

void
bsgfx_instanceSpawners();

#endif