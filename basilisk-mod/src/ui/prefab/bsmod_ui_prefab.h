#ifndef BSMOD_UI_PREFAB_H
#define BSMOD_UI_PREFAB_H

#include <bs_types.h>

void bsmod_pushPrefabMenuWidgets(bs_List* widgets, bs_vec2 background_size);

bool 
bsmod_instancePrefabPreview(
	bsgfx_Widget* widget, 
	bs_vec2* position, 
	int id, 
	bool hovering);


void 
bsmod_onDragPrefab(
	bsmod_DraggingParams params);

void
bsmod_rasterizePrefabIcons();

#endif