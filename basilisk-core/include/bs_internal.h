#ifndef BS_INTERNAL_H
#define BS_INTERNAL_H

#include <bs_types.h>
#include <vulkan.h>

// this is shit
#define BS_PARSE_FORMAT(format, data, len)                         \
    do {                                                           \
        va_list args;                                              \
        va_start(args, format);                                    \
        len = vsnprintf(NULL, 0, format, args);                    \
        va_end(args);                                              \
        if (len >= (sizeof(data) / sizeof(*data))) {               \
            bs_throwBasiliskF(BSX_OUT_OF_BOUNDS,                   \
                "Format %s has a limit of %d characters",          \
                format, sizeof(data) - 1);                         \
        }                                                          \
        va_start(args, format);                                    \
        vsprintf(data, format, args);                              \
        va_end(args);                                              \
    } while (0)

#define BSI_LOG_CREATED(text) (_bs_args.color_log ? (BS_PRINT_GREEN "+ " BS_PRINT_RESET text) : ("+ " text))
#define BSI_LOG_ALTERED(text) (_bs_args.color_log ? (BS_PRINT_YELLOW "/ " BS_PRINT_RESET text) : ("/ " text))
#define BSI_LOG_DELETED(text) (_bs_args.color_log ? (BS_PRINT_RED "- " BS_PRINT_RESET text) : ("- " text))

BSAPI struct VkCommandBuffer_T* bsi_fetchCommands();
BSAPI struct VkDevice_T* bsi_fetchDevice();

BSAPI void
bsi_resizeObjects();

BSAPI void
bsi_resetQueue(
    bs_Queue* queue);

BSAPI void
bsi_pushQueue(
    bs_Queue* queue);

BSAPI void
bsi_nameHandle(
    bs_U64 handle, 
    bs_U32 type, 
    const char* name);

BSAPI void
bsi_nameHandleF(
    bs_U64 handle,
    bs_U32 type,
    const char* format,
    ...);

#define BS_FOREACH_PROC(X) \
    X(PFN_vkCmdInsertDebugUtilsLabelEXT, vkCmdInsertDebugUtilsLabelEXT) \
    X(PFN_vkCmdBeginDebugUtilsLabelEXT, vkCmdBeginDebugUtilsLabelEXT) \
    X(PFN_vkCmdEndDebugUtilsLabelEXT, vkCmdEndDebugUtilsLabelEXT) \
    X(PFN_vkCmdBeginRenderingKHR, vkCmdBeginRenderingKHR) \
    X(PFN_vkCmdEndRenderingKHR, vkCmdEndRenderingKHR) \
    X(PFN_vkCmdTraceRaysKHR, vkCmdTraceRaysKHR) \
    X(PFN_vkGetAccelerationStructureBuildSizesKHR, vkGetAccelerationStructureBuildSizesKHR) \
    X(PFN_vkCreateAccelerationStructureKHR, vkCreateAccelerationStructureKHR) \
    X(PFN_vkCmdBuildAccelerationStructuresKHR, vkCmdBuildAccelerationStructuresKHR) \
    X(PFN_vkGetAccelerationStructureDeviceAddressKHR, vkGetAccelerationStructureDeviceAddressKHR) \
    X(PFN_vkGetRayTracingShaderGroupHandlesKHR, vkGetRayTracingShaderGroupHandlesKHR) \
    X(PFN_vkDestroyAccelerationStructureKHR, vkDestroyAccelerationStructureKHR) \
    X(PFN_vkCreateRayTracingPipelinesKHR, vkCreateRayTracingPipelinesKHR) \

#define BS_STRUCT_GEN(TYPE, FUNC, ...) TYPE FUNC;

typedef struct bs_Procs bs_Procs;
// INTERNAL NOTE: Don't add anything else in here
extern struct bs_Procs {
    BS_FOREACH_PROC(BS_STRUCT_GEN)
} _bs_procs;

BSAPI bs_Procs* bs_procedures();

#endif