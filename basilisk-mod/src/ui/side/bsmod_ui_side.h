#ifndef BSMOD_UI_SIDE_H
#define BSMOD_UI_SIDE_H

#include <bs_types.h>

typedef enum {
    BSMOD_TAB_INSTANCE,
    BSMOD_TAB_MATERIAL,
    BSMOD_TAB_SETTINGS,

    BSMOD_TABS_COUNT,
} bsmod_SideMenuTabId;

typedef struct {
    const char* name;
    bsgfx_AtlasCache* (*cache)();
    void(*push_widgets)(bs_List*, bs_vec2);
    void(*on_click)(bsmod_GridClickParams);
} bsmod_SideMenuTab;

extern bsmod_SideMenuTab _bsmod_side_menu_tabs[BSMOD_TABS_COUNT];

void
bsmod_setSideMenuTab(
    int id,
    bsmod_GridClickParams params);

void 
bsmod_instanceSideMenu(
	bs_vec3 position, 
	bs_vec2 dimensions);

#endif