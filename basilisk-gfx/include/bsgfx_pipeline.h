 
 /**
  bsgfx_pipeline.h
  */

#ifndef BSGFX_PIPELINE_H
#define BSGFX_PIPELINE_H

#include "../bsgfx_contracts.h"

  // Stuff rendered in here will be affected by shadows
#define BSGFX_REQUIRED_FOR_SHADOW_VOLUMES                                       \
    .stencil_front = {                                                          \
        .fail_op = BS_STENCIL_OP_KEEP,                                          \
        .depth_fail_op = BS_STENCIL_OP_KEEP,                                    \
        .pass_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,                           \
        .compare_mask = 0xFF,                                                   \
        .compare_op = BS_COMPARE_OP_LESS_OR_EQUAL,                              \
        .write_mask = 0xFF,                                                     \
    },                                                                          \
    .stencil_back = {                                                           \
        .fail_op = BS_STENCIL_OP_KEEP,                                          \
        .depth_fail_op = BS_STENCIL_OP_KEEP,                                    \
        .pass_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,                           \
        .compare_mask = 0xFF,                                                   \
        .compare_op = BS_COMPARE_OP_LESS_OR_EQUAL,                              \
        .write_mask = 0xFF,                                                     \
    },                                                                          \
    .cull_type = BS_CULL_MODE_NONE                                              \

#define BSGFX_REQUIRED_FOR_SHADOW_STENCIL                                       \
    .depth_comparison = BS_COMPARE_OP_ALWAYS,                                   \
    .stencil_front = {                                                          \
        .compare_op = BS_COMPARE_OP_EQUAL,                                      \
        .compare_mask = 0xFF,                                                   \
        .fail_op = BS_STENCIL_OP_KEEP,                                          \
        .depth_fail_op = BS_STENCIL_OP_KEEP,                                    \
        .pass_op = BS_STENCIL_OP_KEEP,                                          \
    }                                                                           \

#define BSGFX_TRANSPARENT_OPTIONS                                   \
    .src_alpha_factor = BS_BLEND_FACTOR_SRC_ALPHA,                  \
    .dst_alpha_factor = BS_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,        \
    .src_color_factor = BS_BLEND_FACTOR_SRC_ALPHA,                  \
    .dst_color_factor = BS_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,        \
    .color_op = BS_BLEND_OP_ADD,                                    \
    .alpha_op = BS_BLEND_OP_ADD

   /**
    Computes shadow volume geometry on the GPU
    */
	BSGFXAPI void 
	bsgfx_shadowPipe();

	BSGFXAPI void 
	bsgfx_pipeline();

    BSGFXAPI void 
    bsgfx_onDeviceLost();

#endif