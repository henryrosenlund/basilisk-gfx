
 /**
  bsgfx_item.h
  Items can be dropped on the ground, picked up by the player
  Removed from the list when pixked up, added when dropped
  */

#ifndef BSGFX_ITEM_H
#define BSGFX_ITEM_H

#include <bsgfx.h>

enum {
	BSGFX_ITEM_SUBTYPE,
	BSGFX_ITEM_SUBTYPE_VOLUME,
	BSGFX_ITEM_SUBTYPE_HI_RES_SCREEN,

	BSGFX_ITEM_SUBTYPE_COUNT,
};

typedef struct {
	int mesh;
	int material_id;
	bs_Simulation simulation;
} bsgfx_Item;

extern bs_List bsgfx_items;

void
bsgfx_instanceItem(
	bsgfx_Item* item, 
	bs_mat4 transform,
	int material);

void
bsgfx_tickItems();

void
bsgfx_instanceItems();

void 
bsgfx_loadItems();

bsgfx_Item*
bsgfx_spawnItem(
	int item, 
	bs_vec3 position,
	float gravity,
	int material_id);

void
bsgfx_renderItems(
	bs_Pipeline* pipeline,
	int key_start);

void
bsgfx_instanceItemSelectedIcon(
	int item_id);

int 
bsgfx_closestItem(
	bs_vec3 position, 
	float radius);

void 
bsgfx_despawnAllItems();

void 
bsgfx_despawnItem(
	int item_id);

#endif