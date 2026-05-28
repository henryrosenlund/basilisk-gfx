#ifndef BSMOD_UI_TILE_H
#define BSMOD_UI_TILE_H

#include <bs_types.h>

void 
bsmod_pushTileMenuWidgets(
	bs_List* widgets, 
	bs_vec2 background_size);

bool 
bsmod_instanceTilePreview(
	bsgfx_Widget* widget, 
	bs_vec2* position, 
	int id, 
	bool hovering);

void 
bsmod_onDragTile(
	bsmod_DraggingParams params);

#endif