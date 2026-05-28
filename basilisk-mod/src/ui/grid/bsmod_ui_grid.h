#ifndef BSMOD_UI_GRID_H
#define BSMOD_UI_GRID_H

extern bool bsmod_instance_grid_menu;
extern bs_String* bsmod_search_input;

typedef struct {
	int atlas_id;
} bsmod_GridClickParams;

void 
bsmod_instanceGridMenu(
	bs_vec3 position, 
	bs_vec2 dimensions);

#endif