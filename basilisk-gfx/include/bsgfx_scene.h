

 /**
  bsgfx_scene.h
  */

#ifndef BSGFX_SCENE_H
#define BSGFX_SCENE_H

#include <bs_core.h>
#include <bs_math.h>
#include <bs_mem.h>
#include "../bsgfx_contracts.h"

#define BSGFX_MODEL_PATH "resources/models/"
#define BSGFX_SHADER_PATH "resources/shaders/"
#define BSGFX_AUDIO_PATH "resources/audio/"


enum {
    BSGFX_SUBTYPE_BIPYRAMID,
    BSGFX_SUBTYPE_PRIMITIVE_BOX,
    BSGFX_SUBTYPE_PRIMITIVE_SPHERE,
    BSGFX_SUBTYPE_TILE,
    BSGFX_SUBTYPE_TILE_2,
    BSGFX_SUBTYPE_64_HI,
    BSGFX_SUBTYPE_256_HI,
    BSGFX_SUBTYPE_ATLAS_HI,
    BSGFX_SUBTYPE_UI,
    BSGFX_SUBTYPE_UI_COLOR,
    BSGFX_SUBTYPE_UI_STENCIL,
    BSGFX_SUBTYPE_COLOR_PICKER,
    BSGFX_SUBTYPE_COLOR_PICKER_HUE,
    BSGFX_SUBTYPE_COLOR_PICKER_ALPHA,
    BSGFX_SUBTYPE_DITHER,
    BSGFX_SUBTYPE_CORNER_GRADIENT,
    BSGFX_SUBTYPE_TILE_HI,
    BSGFX_SUBTYPE_QUAD_MATERIAL_TEXTURE,
    BSGFX_SUBTYPE_PRIMITIVE_HI,
    BSGFX_SUBTYPE_ATLAS_PREFAB,
    BSGFX_SUBTYPE_ATLAS_PREFAB_TRANSPARENT,
    BSGFX_SUBTYPE_PLANE_MESH,
    BSGFX_SUBTYPE_ATLAS,
    BSGFX_SUBTYPE_CONE_MESH,
    BSGFX_SUBTYPE_SPHERE_MESH,
    BSGFX_SUBTYPE_POINT,
    BSGFX_SUBTYPE_LINE,
    BSGFX_SUBTYPE_LINE_2D,
    BSGFX_SUBTYPE_LINE_DEPTHLESS,

    BSGFX_SUBTYPE_COUNT,
};

typedef struct bsgfx_Scene bsgfx_Scene;



  /*==============================================================================
   * Functions
   *============================================================================*/

    BSGFXAPI extern int _bsgfx_subtypes[BSGFX_SUBTYPE_COUNT];
    BSGFXAPI extern bsgfx_Scene _bsgfx_current_scene;

    BSGFXAPI bsgfx_Scene* 
    bsgfx_currentScene();

    BSGFXAPI void 
    bsgfx_loadScene(
        const char* name);


  /*==============================================================================
   * Structures
   *============================================================================*/

    typedef enum bsgfx_Id bsgfx_Id;

    struct bsgfx_Scene {
        const char* name;
        bs_U64 name_hash;
    };

    typedef enum {
        BSGFX_RESOURCE_PRIMITIVE = BS_RESOURCE_TYPE_COUNT,
        BSGFX_RESOURCE_PREFAB,
        BSGFX_RESOURCE_TILE,
        BSGFX_RESOURCE_LIGHT,

        BSGFX_RESOURCE_TYPE_COUNT
    } bsgfx_ResourceType;

    #define BSGFX_ENUM_GEN(ENUM) ENUM,
    #define BSGFX_STRING_GEN(STRING) #STRING,

    #define BSGFX_IMAGE_IDS(X)                              \
        X(BSGFX_IMAGE_LO_RES_0_DEPTH)                       \
        X(BSGFX_IMAGE_LO_RES_0_COLOR)                       \
        X(BSGFX_IMAGE_LO_RES_0_NORMAL)                      \
        X(BSGFX_IMAGE_LO_RES_0_POSITION)                    \
        X(BSGFX_IMAGE_LO_RES_0_INDEX)                       \
        X(BSGFX_IMAGE_LO_RES_0_FLAGS)                       \
        X(BSGFX_IMAGE_LO_RES_0_VERTEX)                      \
        X(BSGFX_IMAGE_LO_RES_1_COLOR)                       \
        X(BSGFX_IMAGE_HI_RES_0_DEPTH)                       \
        X(BSGFX_IMAGE_TILE)                                 \
        X(BSGFX_IMAGE_ANY)                                  \
        X(BSGFX_IMAGE_64)                                   \
        X(BSGFX_IMAGE_256)                                  \
        X(BSGFX_IMAGE_512)                                  \
        X(BSGFX_IMAGE_RAYTRACE_TEST)                        \
        X(BSGFX_IMAGE_LEVEL_THUMBNAIL)                      \
        X(BSGFX_IMAGE_MINIMAP)

    enum { BSGFX_IMAGE_IDS(BSGFX_ENUM_GEN) BSGFX_IMAGES_COUNT };
    extern int _bsgfx_images;
    BSGFXAPI int bsgfx_images();
#define BSGFX_IMAGES bsgfx_images()

    #define BSGFX_SAMPLER_IDS(X)                            \
        X(BSGFX_SAMPLER_NEAREST)                            \
        X(BSGFX_SAMPLER_LINEAR)

    enum { BSGFX_SAMPLER_IDS(BSGFX_ENUM_GEN) BSGFX_SAMPLERS_COUNT };
    extern int _bsgfx_samplers;
    BSGFXAPI int bsgfx_samplers();
#define BSGFX_SAMPLERS bsgfx_samplers()

    #define BSGFX_BUFFER_IDS(X)                             \
        X(BSGFX_BUFFER_JOINTS)                              \
        X(BSGFX_BUFFER_INSTANCE_METADATA)                   \
        X(BSGFX_BUFFER_LO_RES_CURSOR_READS)                 \
        X(BSGFX_BUFFER_LO_RES_SCREENSHOT)                   \
        X(BSGFX_BUFFER_MATERIALS)                           \
        X(BSGFX_BUFFER_MINIMAP)                             \
        X(BSGFX_BUFFER_BINDING_TABLE)

    enum { BSGFX_BUFFER_IDS(BSGFX_ENUM_GEN) BSGFX_BUFFERS_COUNT };
    extern int _bsgfx_buffers;
    BSGFXAPI int bsgfx_buffers();
#define BSGFX_BUFFERS bsgfx_buffers()

    #define BSGFX_BATCH_IDS(X)                              \
        X(BSGFX_BATCH_VOLUME_COMPUTED)                      \
        X(BSGFX_BATCH_PREFAB_SHADOWS)                       \
        X(BSGFX_BATCH_VOLUME_INSTANCED)                     \
        X(BSGFX_BATCH_VOLUME_SCREEN)                        \
        X(BSGFX_BATCH_SCREEN)                               \
        X(BSGFX_BATCH_LINE_INSTANCED)                       \
        X(BSGFX_BATCH_POINT_INSTANCED)                      \
        X(BSGFX_BATCH_SPHERE_INSTANCED)                     \
        X(BSGFX_BATCH_BONE_INSTANCED)                       \
        X(BSGFX_BATCH_MESH_INSTANCED)                       \
        X(BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED)            \
        X(BSGFX_BATCH_FOLIAGE)                              \
        X(BSGFX_BATCH_QUAD_INSTANCED)                       \
        X(BSGFX_BATCH_TEXT_INSTANCED)                       \
        X(BSGFX_BATCH_ITEMS)                                \
        X(BSGFX_BATCH_PRIMITIVE_TILES)

    enum { BSGFX_BATCH_IDS(BSGFX_ENUM_GEN) BSGFX_BATCHES_COUNT };
    extern int _bsgfx_batches;
    BSGFXAPI int bsgfx_batches();
#define BSGFX_BATCHES bsgfx_batches()

    #define BSGFX_RENDERER_IDS(X)                           \
        X(BSGFX_RENDERER_LO_RES)                            \
        X(BSGFX_RENDERER_HI_RES)                            \

    enum { BSGFX_RENDERER_IDS(BSGFX_ENUM_GEN) BSGFX_RENDERERS_COUNT };
    extern int _bsgfx_renderers;
    BSGFXAPI int bsgfx_renderers();
#define BSGFX_RENDERERS bsgfx_renderers()

    #define BSGFX_QUEUE_IDS(X)                              \
        X(BSGFX_QUEUE_GRAPHICS)                             \
        X(BSGFX_QUEUE_COMPUTE)

    enum { BSGFX_QUEUE_IDS(BSGFX_ENUM_GEN) BSGFX_QUEUES_COUNT };
    extern int _bsgfx_queues;
    BSGFXAPI int bsgfx_queues();
#define BSGFX_QUEUES bsgfx_queues()

    #define BSGFX_RAY_TRACER_IDS(X)                         \
        X(BSGFX_RAY_TRACER_MAIN)

    enum { BSGFX_RAY_TRACER_IDS(BSGFX_ENUM_GEN) BSGFX_RAY_TRACERS_COUNT };
    extern int _bsgfx_ray_tracers;
    BSGFXAPI int bsgfx_rayTracers();
#define BSGFX_RAY_TRACERS bsgfx_rayTracers()

    #define BSGFX_ATLAS_IDS(X)                              \
        X(BSGFX_ATLAS_ANY)

    enum { BSGFX_ATLAS_IDS(BSGFX_ENUM_GEN) BSGFX_ATLASES_COUNT };
    extern int _bsgfx_atlases;
    BSGFXAPI int bsgfx_atlases();
#define BSGFX_ATLASES bsgfx_atlases()

    #define BSGFX_FONT_IDS(X)                               \
        X(BSGFX_FONT_STANDARD)                              \
        X(BSGFX_FONT_SMALL)                                 \
        X(BSGFX_FONT_TEMPLE)                                \
        X(BSGFX_FONT_CONSOLAS)                              \
        X(BSGFX_FONT_ARIAL_16)                              \
        X(BSGFX_FONT_ARIAL_24)                              \
        X(BSGFX_FONT_ARIAL_32)                              \
        X(BSGFX_FONT_ARIAL_48)

    enum { BSGFX_FONT_IDS(BSGFX_ENUM_GEN) BSGFX_FONTS_COUNT };
    extern int _bsgfx_fonts;
    BSGFXAPI int bsgfx_fonts();
#define BSGFX_FONTS bsgfx_fonts()



  /*==============================================================================
   * Dependencies
   *============================================================================*/

    #define BSGFX_DEPENDENCY_ALWAYS                         \
        BSGFX_IMAGE_64,                                     \
        BSGFX_IMAGE_256,                                    \
        BSGFX_IMAGE_512,                                    \
        BSGFX_SAMPLER_LINEAR

    #define BSGFX_DEPENDENCY_PLAYER                         \
        BSGFX_BATCH_BONE_INSTANCED,                         \
        BSGFX_BATCH_MESH_INSTANCED,                         \
        BSGFX_BUFFER_JOINTS                                 \

    #define BSGFX_DEPENDENCY_TILE                           \
        BSGFX_IMAGE_TILE                                    \

    #define BSGFX_DEPENDENCY_LO_RES                         \
        BSGFX_QUEUE_GRAPHICS,                               \
        BSGFX_IMAGE_LO_RES_0_DEPTH,                         \
        BSGFX_IMAGE_LO_RES_0_COLOR,                         \
        BSGFX_IMAGE_LO_RES_0_NORMAL,                        \
        BSGFX_IMAGE_LO_RES_0_POSITION,                      \
        BSGFX_IMAGE_LO_RES_0_INDEX,                         \
        BSGFX_IMAGE_LO_RES_0_FLAGS,                         \
        BSGFX_IMAGE_LO_RES_0_VERTEX,                        \
        BSGFX_IMAGE_LO_RES_1_COLOR,                         \
        BSGFX_RENDERER_LO_RES                               \

    #define BSGFX_DEPENDENCY_SHADOWS                        \
        BSGFX_DEPENDENCY_LO_RES,                            \
        BSGFX_BUFFER_INSTANCE_METADATA,                     \
        BSGFX_BATCH_VOLUME_COMPUTED,                        \
        BSGFX_BATCH_PREFAB_SHADOWS,                         \
        BSGFX_BATCH_VOLUME_DOWN_COMPUTED,                   \
        BSGFX_BATCH_VOLUME_INSTANCED,                       \
        BSGFX_BATCH_VOLUME_SCREEN,                          \
        BSGFX_QUEUE_COMPUTE                                 \

    #define BSGFX_DEPENDENCY_HI_RES                         \
        BSGFX_RENDERER_HI_RES,                              \
        BSGFX_IMAGE_HI_RES_0_DEPTH                          \

    #define BSGFX_DEPENDENCY_FOLIAGE                        \
        BSGFX_BATCH_FOLIAGE                                 \

    #define BSGFX_DEPENDENCY_ATLAS                          \
        BSGFX_SAMPLER_NEAREST,                              \
        BSGFX_IMAGE_ANY                                     \

    #define BSGFX_DEPENDENCY_INGAME                         \
        BSGFX_DEPENDENCY_HI_RES,                            \
        BSGFX_DEPENDENCY_LO_RES,                            \
        BSGFX_DEPENDENCY_SHADOWS,                           \
        BSGFX_DEPENDENCY_ATLAS,                             \
        BSGFX_DEPENDENCY_FOLIAGE,                           \
        BSGFX_DEPENDENCY_TILE,                              \
        BSGFX_DEPENDENCY_PLAYER,                            \
        BSGFX_RAY_TRACER_MAIN,                              \
        BSGFX_IMAGE_RAYTRACE_TEST,                          \
        BSGFX_BATCH_ITEMS,                                  \
        BSGFX_BUFFER_MATERIALS,                             \
        BSGFX_BUFFER_MINIMAP,                               \
        BSGFX_ATLAS_ANY,                                    \
        BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED,              \
       /* images*/                                          \
        BSGFX_IMAGE_64,                                     \
        BSGFX_IMAGE_256,                                    \
        BSGFX_IMAGE_512,                                    \
        BSGFX_IMAGE_MINIMAP,                                \
       /* batches */                                        \
        BSGFX_BATCH_QUAD_INSTANCED,                         \
        BSGFX_BATCH_SCREEN,                                 \
        BSGFX_BATCH_SPHERE_INSTANCED,                       \
        BSGFX_BATCH_PRIMITIVE_TILES,                        \
       /* fonts */                                          \
        BSGFX_FONT_STANDARD,                                \
        BSGFX_FONT_TEMPLE,\
        BSGFX_FONT_CONSOLAS,\
        BSGFX_FONT_ARIAL_16,

    #define BSGFX_DEPENDENCY_TEXT                           \
        BSGFX_BATCH_QUAD_INSTANCED,                         \
        BSGFX_BATCH_TEXT_INSTANCED                          \

    #define BSGFX_DEPENDENCY_DEBUG                          \
        BSGFX_DEPENDENCY_TEXT,                              \
        BSGFX_BUFFER_LO_RES_CURSOR_READS,                   \
        BSGFX_BUFFER_LO_RES_SCREENSHOT,                     \
        BSGFX_FONT_SMALL,                                   \
        BSGFX_BATCH_LINE_INSTANCED,                         \
        BSGFX_BATCH_POINT_INSTANCED                         \

#endif