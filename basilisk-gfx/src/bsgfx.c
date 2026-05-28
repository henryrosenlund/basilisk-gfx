#include <bs_window.h>
#include <bs_log.h>
#include <bs_images.h>
#include <bs_shaders.h>
#include <bs_ini.h>
#include <bs_audio.h>

#include <complex.h>
#include <math.h>
#include <assert.h>
#include <inttypes.h>

#include <bsgfx.h>
#include <bsgfx_pipeline.h>
#include <bsgfx_scene.h>
#include <bsgfx_instance.h>
#include <bsgfx_material.h>
#include <bssteam.h>
#include <bssteam_controller.h>
#include <bsgfx_collider.h>

#include <spawners/item/bsgfx_item.h>

#include <types/bsgfx_type.h>
#include <types/prefab/bsgfx_prefab.h>
#include <types/foliage/bsgfx_foliage.h>
#include <types/spawner/bsgfx_spawner.h>
#include <types/primitive/bsgfx_primitive.h>
#include <types/tile/bsgfx_tile.h>

#include <UI/bsgfx_ui.h>

#define VULKAN_H_
#include <GFSDK_Aftermath_GpuCrashDump.h>
#include <GFSDK_Aftermath_GpuCrashDumpDecoding.h>
#include <GFSDK_Aftermath.h>

struct Poser* _poser = NULL;

bs_Model* _bsgfx_prefab_model = NULL;
bs_String* _bsgfx_variadic = NULL;
HINSTANCE _bsgfx_bsmod_dll = NULL;
int _bsgfx_package = -1;

bsgfx_Callbacks _bsgfx_callbacks = { 0 };
bsgfx_Settings _bsgfx_settings = { 0 };

bs_mat4* _bsgfx_shader_joints = NULL;
bs_U32 _bsgfx_num_shader_joints = 0;

bsgfx_Procedures _bsgfx_procs = { 0 };
bsgfx_Controller _bsgfx_ctrl;
bsgfx_Controller _bsgfx_ctrl_last;
bsgfx_Controller _bsgfx_ctrl_last_fixed;

HINSTANCE bsgfx_bsmodDll() {
    return _bsgfx_bsmod_dll;
}

bsgfx_Application _bsgfx_app;

bsgfx_Application* bsgfx_app() {
    return &_bsgfx_app;
}

bsgfx_Callbacks* bsgfx_callbacks() {
    return &_bsgfx_callbacks;
}

bsgfx_Settings* bsgfx_settings() {
    return &_bsgfx_settings;
}

bs_Model* bsgfx_prefabModel() {
    return _bsgfx_prefab_model;
}

int bsgfx_package() {
    return _bsgfx_package;
}

struct Poser* poser() {
    return _poser;
}

static void bsgfx_configure() {
    _bsgfx_images = bs_configureSource(BS_OBJECT_IMAGE, BSGFX_IMAGES_COUNT, (const char*[]) { BSGFX_IMAGE_IDS(BS_STRING_GEN) });
    _bsgfx_samplers = bs_configureSource(BS_OBJECT_SAMPLER, BSGFX_SAMPLERS_COUNT, (const char* []) { BSGFX_SAMPLER_IDS(BS_STRING_GEN) });
    _bsgfx_buffers = bs_configureSource(BS_OBJECT_BUFFER, BSGFX_BUFFERS_COUNT, (const char* []) { BSGFX_BUFFER_IDS(BS_STRING_GEN) });
    _bsgfx_queues = bs_configureSource(BS_OBJECT_QUEUE, BSGFX_QUEUES_COUNT, (const char* []) { BSGFX_QUEUE_IDS(BS_STRING_GEN) });
    _bsgfx_batches = bs_configureSource(BS_OBJECT_BATCH, BSGFX_BATCHES_COUNT, (const char* []) { BSGFX_BATCH_IDS(BS_STRING_GEN) });
    _bsgfx_renderers = bs_configureSource(BS_OBJECT_RENDERER, BSGFX_RENDERERS_COUNT, (const char* []) { BSGFX_RENDERER_IDS(BS_STRING_GEN) });
    _bsgfx_ray_tracers = bs_configureSource(BS_OBJECT_RAY_TRACER, BSGFX_RAY_TRACERS_COUNT, (const char* []) { BSGFX_RAY_TRACER_IDS(BS_STRING_GEN) });
    _bsgfx_fonts = bs_configureSource(BS_OBJECT_FONT, BSGFX_FONTS_COUNT, (const char* []) { BSGFX_FONT_IDS(BS_STRING_GEN) });
    _bsgfx_atlases = bs_configureSource(BS_OBJECT_ATLAS, BSGFX_ATLASES_COUNT, (const char* []) { BSGFX_ATLAS_IDS(BS_STRING_GEN) });

    bs_configureAttribute("bsgfx_VolumeId", BS_FORMAT_R32_SFLOAT);
    bs_configureAttribute("bsgfx_Index", BS_FORMAT_R32_UINT);

   // static const char* strs[] = { BSGFX_FOREACH_ID(BSGFX_STRING_GEN) };
   // for (int i = 0; i < _BSGFX_NUM_OBJECTS; i++)
   //     bs_nameId(i, strs[i]);
}

static void bsgfx_resize() {
    bs_Renderer* lo_res = bs_fetch(BSGFX_RENDERERS, BSGFX_RENDERER_LO_RES)->renderer;
    if (lo_res) {
        bs_ivec2 lo_resolution = bs_resolution();
        lo_resolution.x /= BSGFX_PIXEL_SCALE;
        lo_resolution.y /= BSGFX_PIXEL_SCALE;

        bs_resizeImage(bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_COLOR)->image, lo_resolution, 0);
        bs_resizeImage(bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_DEPTH)->image, lo_resolution, 0);

        bs_pushDescriptors();

        bs_resizeRenderer(lo_res, lo_resolution);
    }
}

static void bssteam_pollActions() {
    /*
    if (_bsgfx_ctrl.handle) {
        if (_poser->menu_open) {
            bs_U64 handle = bssteam_activateActionSet(_bsgfx_ctrl.handle, "MenuControls");
            if (_bsgfx_ctrl.ingame.action_set_handle != handle)
                memset(&_bsgfx_ctrl, 0, sizeof(_bsgfx_ctrl));
            _bsgfx_ctrl.ingame.action_set_handle = handle;

            bssteam_pollButton(_bsgfx_ctrl.handle, &_bsgfx_ctrl.menu.up, "menuUp");
            bssteam_pollButton(_bsgfx_ctrl.handle, &_bsgfx_ctrl.menu.down, "menuDown");
            bssteam_pollButton(_bsgfx_ctrl.handle, &_bsgfx_ctrl.menu.left, "menuLeft");
            bssteam_pollButton(_bsgfx_ctrl.handle, &_bsgfx_ctrl.menu.right, "menuRight");
            bssteam_pollButton(_bsgfx_ctrl.handle, &_bsgfx_ctrl.menu.affirm, "affirm");
            bssteam_pollButton(_bsgfx_ctrl.handle, &_bsgfx_ctrl.menu.cancel, "cancel");
        }
        else {
            bs_U64 handle = bssteam_activateActionSet(_bsgfx_ctrl.handle, "GameControls");
            if (_bsgfx_ctrl.ingame.action_set_handle != handle)
                memset(&_bsgfx_ctrl, 0, sizeof(_bsgfx_ctrl));
            _bsgfx_ctrl.ingame.action_set_handle = handle;

            bssteam_pollJoystick(_bsgfx_ctrl.handle, &_bsgfx_ctrl.ingame.move, "move");
            bssteam_pollButton(_bsgfx_ctrl.handle, &_bsgfx_ctrl.ingame.interact, "interact");
            bssteam_pollButton(_bsgfx_ctrl.handle, &_bsgfx_ctrl.ingame.jump, "jump");
            bssteam_pollButton(_bsgfx_ctrl.handle, &_bsgfx_ctrl.ingame.prepare_skate, "prepareSkate");
        }
    }
    else
        memset(&_bsgfx_ctrl, 0, sizeof(_bsgfx_ctrl));
        */
    if (_poser->menu_open) {
        _bsgfx_ctrl.menu.up.pressed = bs_keyDownOnce(BS_KEY_UP) ? true : _bsgfx_ctrl.menu.up.pressed;
        _bsgfx_ctrl.menu.down.pressed = bs_keyDownOnce(BS_KEY_DOWN) ? true : _bsgfx_ctrl.menu.down.pressed;
        _bsgfx_ctrl.menu.affirm.pressed = bs_keyDownOnce(BS_KEY_ENTER) ? true : _bsgfx_ctrl.menu.affirm.pressed;
    }
    else {
        _bsgfx_ctrl.ingame.move.v.x = bs_keyDown(BS_KEY_A) ? -1.0 : _bsgfx_ctrl.ingame.move.v.x;
        _bsgfx_ctrl.ingame.move.v.x = bs_keyDown(BS_KEY_D) ? 1.0 : _bsgfx_ctrl.ingame.move.v.x;
        _bsgfx_ctrl.ingame.move.v.y = bs_keyDown(BS_KEY_W) ? 1.0 : _bsgfx_ctrl.ingame.move.v.y;
        _bsgfx_ctrl.ingame.move.v.y = bs_keyDown(BS_KEY_S) ? -1.0 : _bsgfx_ctrl.ingame.move.v.y;
    }
}

void bsgfx_openMenu() {
    _poser->menu_open = true;
    bssteam_pollActions();
}

void bsgfx_closeMenu() {
    _poser->menu_open = false;
    bssteam_pollActions();
}

static void bsgfx_tick() {
    _poser->menu_blocked = false;
    _bsgfx_ctrl_last = _bsgfx_ctrl;
    _bsgfx_ctrl.ingame.move.v = bs_v2V1(0.0);

    bool controller_found = (bool)_bsgfx_ctrl.handle;
    _bsgfx_ctrl.handle = bssteam_pollController(0);

    if (!controller_found && (bool)_bsgfx_ctrl.handle)
        bs_infoF("Controller connected\n");

    static int timer;
    const double time_scale = 0.0;
    
    _poser->time += time_scale * bs_deltaTime();
    _poser->second = ((int)_poser->time) % 86400;
    _poser->hour = _poser->second / 3600;
    _poser->minute = (_poser->second % 3600) / 60;

    float day_fraction = (float)_poser->time / 86400.0f;
    float angle = day_fraction * 2.0f * BS_PI;

    _poser->sun_direction = bs_v3NormalizeV3(-sinf(angle), cosf(angle), -0.48);

    bssteam_pollActions();
    
    bssteam_tickSteam();
    //bsgfx_instanceItems();

    bs_vec2 resolution = { .x = (float)bs_resolution().x, .y = (float)bs_resolution().y };
    bs_mat4 screen_camera_proj = bs_ortho(0, resolution.x, 0, resolution.y, -1000, 1000);
    bs_mat4 screen_camera_view = bs_lookAt(bs_v3V1(0), bs_v3(0, 0, -1), bs_v3(0, 1, 0));
    _poser->screen_camera.result = bs_m4Mul(screen_camera_proj, screen_camera_view);

    bsgfx_instancePrimitives();
    if (_bsgfx_prefab_model)
        bsgfx_instancePrefabs();
    bsgfx_instanceTiles();


    //if (bs_charDown(' '))
    //    bs_advance();
    //bsgfx_instanceEntities();

//    if (bsgfx_scene != BSGFX_SCENE_MENU)
//        bsgfx_instanceMinimap();

    if (_bsgfx_procs.bsmod_onGfxRender)
        _bsgfx_procs.bsmod_onGfxRender();
    if (_bsgfx_callbacks.tick)
        _bsgfx_callbacks.tick();

    bsgfx_tickInstances();

    bsgfx_pipeline();
    bsgfx_tickMaterials();
}

static void bsgfx_fixedTick() {
    _bsgfx_ctrl_last_fixed = _bsgfx_ctrl;
 //   bsgfx_tickItems();

    if (_bsgfx_callbacks.fixedTick)
        _bsgfx_callbacks.fixedTick();
}

static void bsgfx_onGpuCrash(const void* crash_dump, const bs_U32 crash_dump_size, void* params) {
    bs_saveFile("aftermath.nv-gpudmp", crash_dump, crash_dump_size);
}

static void bsgfx_onShaderDebugInfo(const void* info, const uint32_t size, void* params) {
    GFSDK_Aftermath_ShaderDebugInfoIdentifier identifier = { 0 };
    GFSDK_Aftermath_Result result = GFSDK_Aftermath_GetShaderDebugInfoIdentifier(GFSDK_Aftermath_Version_API, info, size, &identifier);

    if (result == GFSDK_Aftermath_Result_Success) {
        bs_saveFileF(info, size, "%016" PRIx64 ".nvdbg", identifier.id[0]);
    }
}

void bsgfx_onGpuCrashDescription(PFN_GFSDK_Aftermath_AddGpuCrashDumpDescription add_description, void* params) {
   // add_description(GFSDK_Aftermath_GpuCrashDumpDescriptionKey_ApplicationName, "Hello Nsight Aftermath");
}

static inline const char* bsgfx_GFSDK_resultName(GFSDK_Aftermath_Result result) {
    switch (result) {
    case GFSDK_Aftermath_Result_NotAvailable: return "Not available";
    case GFSDK_Aftermath_Result_Fail: return "Fail";
    case GFSDK_Aftermath_Result_FAIL_VersionMismatch: return "Version mismatch";
    case GFSDK_Aftermath_Result_FAIL_NotInitialized: return "Not initialized";
    case GFSDK_Aftermath_Result_FAIL_InvalidAdapter: return "Invalid adapter";
    case GFSDK_Aftermath_Result_FAIL_InvalidParameter: return "Invalid parameter";
    case GFSDK_Aftermath_Result_FAIL_Unknown: "Unknown";
    case GFSDK_Aftermath_Result_FAIL_ApiError: return "API error";
    case GFSDK_Aftermath_Result_FAIL_NvApiIncompatible: return "NVIDIA API incompatible";
    case GFSDK_Aftermath_Result_FAIL_GettingContextDataWithNewCommandList: return "Getting context data with new command list";
    case GFSDK_Aftermath_Result_FAIL_AlreadyInitialized: return "Already initialized";
    case GFSDK_Aftermath_Result_FAIL_D3DDebugLayerNotCompatible: return "D3D debug layer not compatible";
    case GFSDK_Aftermath_Result_FAIL_DriverInitFailed: return "Driver initializaion failed";
    case GFSDK_Aftermath_Result_FAIL_DriverVersionNotSupported: return "Driver version not supported";
    case GFSDK_Aftermath_Result_FAIL_OutOfMemory: return "Out of memory";
    case GFSDK_Aftermath_Result_FAIL_GetDataOnBundle: return "Get data on bundle";
    case GFSDK_Aftermath_Result_FAIL_GetDataOnDeferredContext: return "Get data on deferred context";
    case GFSDK_Aftermath_Result_FAIL_FeatureNotEnabled: return "Feature not enabled";
    case GFSDK_Aftermath_Result_FAIL_NoResourcesRegistered: return "No resources registered";
    case GFSDK_Aftermath_Result_FAIL_ThisResourceNeverRegistered: return "This resource never registered";
    case GFSDK_Aftermath_Result_FAIL_NotSupportedInUWP: return "Not supported in UWP";
    case GFSDK_Aftermath_Result_FAIL_D3dDllNotSupported: return "D3D DLL not supported";
    case GFSDK_Aftermath_Result_FAIL_D3dDllInterceptionNotSupported: return "D3D DLL interception not supported";
    case GFSDK_Aftermath_Result_FAIL_Disabled: return "Disabled";
    case GFSDK_Aftermath_Result_FAIL_NotSupportedOnContext: return "Not supported on context";
    }

    return "Invalid GFSDK error";
}


void bsgfx_logGFSDK(GFSDK_Aftermath_Result result) {
    if (result != GFSDK_Aftermath_Result_Success)
        bs_infoF("GFSDK Aftermath error:\n%s\n", bsgfx_GFSDK_resultName(result));
}

void bsgfx_checkGFSDK(GFSDK_Aftermath_Result result) {
    if (result != GFSDK_Aftermath_Result_Success) {
        bs_throwBasilisk(BSX_GENERAL);
    }
}

void bsgfx_setCamera(const bs_mat4* proj, const bs_mat4* view) {
    _poser->camera.proj = *proj;
    _poser->camera.view = *view;
    _poser->camera.result = bs_m4Mul(*proj, *view);
}

void bsgfx_ini(const char* name, bs_U32 width, bs_U32 height, int argc, char* argv[]) {
    for (int i = 0; i < BSGFX_SUBTYPE_COUNT; i++)
        _bsgfx_subtypes[i] = -1;

    _bsgfx_app.name = name;

    _poser = bs_malloc(sizeof(struct Poser));
    *_poser = (struct Poser){
        .time = 10.8 * 60 * 60,
        .menu_open = true, // main menu
        .sweep_collisions = bs_list(sizeof(bsgfx_SweepCollision), 64),
    };

    bs_parseArgs(argc, argv);

#ifdef _DEBUG
    const char* args[] = { "--cmd-log", "--color-log", "--use-lisk", "--use-validation-layers" };
    bs_parseArgs(sizeof(args) / sizeof(char*), args);
#endif
    
    _bsgfx_bsmod_dll = LoadLibrary("basilisk-mod.dll");
    if (_bsgfx_bsmod_dll) {
        bs_Procedure procedures[] = {
            BSGFX_FOREACH_PROC(BS_STRING_GEN_2)
        };
        bs_queryProcedures(procedures, sizeof(procedures) / sizeof(*procedures), _bsgfx_bsmod_dll, &_bsgfx_procs);
    }

    bs_window(width, height, name, NULL);

    /*
    GFSDK_Aftermath_Result result = GFSDK_Aftermath_EnableGpuCrashDumps(
        GFSDK_Aftermath_Version_API,
        GFSDK_Aftermath_GpuCrashDumpWatchedApiFlags_Vulkan,
        GFSDK_Aftermath_GpuCrashDumpFeatureFlags_Default,
        bsgfx_onGpuCrash,
        bsgfx_onShaderDebugInfo,
        bsgfx_onGpuCrashDescription,
        NULL,
        NULL);
    */

    if (_bsgfx_procs.bsmod_onIni)
        _bsgfx_procs.bsmod_onIni();

    if (_bsgfx_procs.bsmod_onTrack && bs_args()->track_changes)
        _bsgfx_procs.bsmod_onTrack();

    if (_bsgfx_procs.bsmod_onLateIni)
        _bsgfx_procs.bsmod_onLateIni();

    bs_except(BSX_NOT_FOUND);
    _bsgfx_package = bs_loadPackage(BSGFX_CONTENT_PATH);
    bs_except(0);

    bssteam_iniSteam();
    bssteam_iniSteamInput();
#ifdef _DEBUG
    bssteam_overrideManifestFile("resources/iga.vdf");
#endif
    bsgfx_configure();
    bs_ini();
    bs_iniAudio();
    bs_loadBindings(_bsgfx_package, "bindings");

   // bs_pause();

    if (_bsgfx_callbacks.ini)
        _bsgfx_callbacks.ini();

    bs_tick(bsgfx_tick, bsgfx_fixedTick);

    if (bs_exists(BSGFX_RAY_TRACERS, BSGFX_RAY_TRACER_MAIN))
        bs_destroyRayTracer(bs_fetch(BSGFX_RAY_TRACERS, BSGFX_RAY_TRACER_MAIN)->ray_tracer);

    bs_free(_poser);
    // todo destroy dll
}