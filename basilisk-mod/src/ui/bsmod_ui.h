#ifndef BSMOD_UI_H
#define BSMOD_UI_H

#define BSMOD_DEFAULT_RADIUS 5.0
#define BSMOD_TAB_BAR_HEIGHT 20.0
#define BSMOD_GRID_SIDE_MENU_SPACE 16.0
#define BSGFX_SIDE_MENU_WIDTH 400
#define BSMOD_INPUT_HEIGHT 16

#define BSMOD_UI_BASE_TEXT_MATERIAL $bsmod_grey_230

#include <ui/bsgfx_ui.h>
#include <bsmod.h>

typedef struct {
    int t;
} bsmod_DraggingParams;

void
bsmod_renderBillboards();

void 
bsmod_instanceUI();

void bsmod_pushVecNWidget(bs_List* widgets, const char* name, bs_vec3 offset, float width, float* v, int n);

void bsmod_pushInputWidget(
    bs_List* widgets,
    void* value,
    bs_vec3 offset,
    float width,
    int name_padding,
    bool skip_advance,
    bool is_last,
    bool has_buttons,
    const char* name);

static inline bsgfx_Scrollbar bsmod_scrollbar(int* scroll) {
    return (bsgfx_Scrollbar) {
        .value = scroll,
        .substeps_count = 4,
        .padding = 8,
        .width = 16.0,
        .border_radius = BSMOD_DEFAULT_RADIUS,

        .material = $bsmod_grey_138()->id,
        .outline_material = $bsmod_grey_30()->id,
        .background_material = $bsmod_grey_61()->id,

        .button_icon_material = $bsmod_grey_61()->id,
        .button_background_material = $bsmod_grey_138()->id,
        .button_outline_material = $bsmod_grey_30()->id,
    };
}

static inline bsgfx_Widget bsmod_dividerWidget(float width, int indent) {
    return (bsgfx_Widget) {
       // .name = "",
        .type = BSGFX_WIDGET_ICON,
        .offset.x = indent,
        .icon = {
            .atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas,
            .name = "white",
            .material_id = $context_menu_grey_text_material()->id,
            .scale = { width - indent * 2 - 1, 1 },
        }
    };
}

static inline bsgfx_Widget bsmod_iconWidget(bsgfx_AtlasCache* cache, float align_height, bs_vec3 offset, bs_U32 advance_flags) {
    return (bsgfx_Widget) {
        .type = BSGFX_WIDGET_ICON,
        .icon = {
            .atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas,
            .atlas_subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
            .type = BSGFX_ICON_ATLAS,
            .name = cache->name, // todo skip query
            .material_id = $white_material()->id,
        },
        .advance_flags = advance_flags,
        .material_id = $white_material()->id,
        .align_height = align_height,
        .offset = offset,
    };
}

#endif