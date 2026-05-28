#ifndef BSMOD_SELECT_H
#define BSMOD_SELECT_H

#include <bsmod.h>
#define BSMOD_IDS &bsmod.selected_ids
#define BSMOD_TILE_IDS &bsmod.selected_tiles

void 
bsmod_selectHoveringTypes();

BSMODAPI void
bsgfx_applyGridMenuDragging(
	int id,
	bool hovering,
	int type,
	char* hint,
	const char* (*info_menu)(bs_List*),
	void (*on_show_info)(int));

bsgfx_TypeId 
bsmod_queryType(
	const char* plural);

void 
bsmod_delete(
	bsgfx_TypeId type_id, 
	int id);

void 
bsmod_deleteSelected(
	bsgfx_TypeId type_id);

void 
bsmod_saveType(
	bsgfx_TypeId id, 
	const char* comment_format, 
	...);

void* 
bsmod_add(
	bsgfx_TypeId id, 
	void* data);

bool 
bsmod_isSelected(
	bs_List* list,
	bsgfx_TypeId type, 
	int id);

void 
bsmod_select(
	bs_List* list,
	bsgfx_TypeId type,
	int id);

void 
bsmod_deselectAll();

void 
bsmod_deselectRange(
	bs_List* list,
	int first, 
	int count);

void 
bsmod_deselectIndex(
	bs_List* list,
	int id);

void 
bsmod_deselect(
	bs_List* list,
	int id);

int 
bsmod_firstSelectedId(
	bs_List* list);

int 
bsmod_lastSelectedId(
	bs_List* list);

void* 
bsmod_removeFlexible(
	bsgfx_TypeId type_id, 
	int id);

void* 
bsmod_addFlexible(
	bsgfx_TypeId type_id, 
	int id, 
	void* data);

void 
bsmod_readHoveringOutputs();

void 
bsmod_readHoveringInstanceData();

void 
bsmod_readHoveringVertex();

void 
bsmod_editSelectedType();

BSMODAPI void
bsmod_ensureTypeVersionsAreUpToDate(
	int package_id);

#endif