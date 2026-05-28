#ifndef BSMOD_UI_CONTEXT_H
#define BSMOD_UI_CONTEXT_H

#include <bs_types.h>
#include <bsgfx_cache.h>

#define BSMOD_CONTEXT_MENU_BUTTON_HEIGHT 20
#define BSMOD_CONTEXT_MENU_PADDING 4

void 
bsmod_instanceTileContextMenu(
	bs_vec3 position, 
	bs_vec2 size);

void
bsmod_instanceContextMenu(
	bs_List* widgets,
	bs_vec3 position,
	bs_vec2 size);

void
bsmod_pushContextMenuButton(
	bs_List* widgets,
	bs_vec2 menu_size,
	bs_vec3 icon_offset,
	bsgfx_AtlasCache* icon,
	const char* name,
	int indent,
	bool(*action)(struct bsgfx_Widget*),
	bool expandable);

#endif