#ifndef BSMOD_UI_MATERIAL_H
#define BSMOD_UI_MATERIAL_H

#include <bs_types.h>
#include <ui/grid/bsmod_ui_grid.h>
#include <ui/bsmod_ui.h>

void 
bsmod_pushMaterialWidgets(
	bs_List* widgets, 
	bs_vec2 background_size);

void
bsmod_onDragMaterial(
	bsmod_DraggingParams params);

void
bsmod_onClickMaterialMenu(
	bsmod_GridClickParams params);

void
bsmod_rasterizeMaterialIcons();

#endif