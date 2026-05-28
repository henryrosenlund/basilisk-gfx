#ifndef BSMOD_UI_PRIMITIVE_H
#define BSMOD_UI_PRIMITIVE_H

#include <bsmod.h>
#include <ui/bsmod_ui.h>

bool 
bsmod_instancePrimitivePreview(
	bsgfx_Widget* widget, 
	bs_vec2* position, 
	int id, 
	bool hovering);

void 
bsmod_onDragPrimitive(
	bsmod_DraggingParams params);

BSMODAPI void
bsmod_rasterizePrimitiveIcons();

#endif