
 /**
  bs_objects.h
  Object managment system
  */

#ifndef BS_OBJECTS_H
#define BS_OBJECTS_H

#include <bs_types.h>




  /*==============================================================================
   * Macros
   *============================================================================*/

   /**
    Hack to determine the size of a "swap"
    Items that can be double/triple buffered are identified by the flexible array member '_' at the end of each object
    */
    #define BS_SWAP_SIZE(type) (sizeof(*((type*)NULL)->_))
    #define BS_SWAPS_COUNT(flags) ((flags & BS_OBJECT_HAS_SWAPS_BIT) ? bs_settings()->frames_in_flight : 1)

    BSAPI void bs_assertSourceIsType(int source_id, bs_ObjectType object_type);
    BSAPI const char* bs_idName(bs_U32 source_id, bs_U32 id);
    BSAPI bs_Object* bs_object(
        bs_U32 source_id, 
        bs_U32 id,
        size_t size, 
        size_t flexible_size, 
        int flexible_count, 
        bs_U32 flags);

#define BS_OBJECT(type, source_id, id, swaps_count, flags) \
    bs_object(source_id, id, sizeof(type), BS_SWAP_SIZE(type), swaps_count, flags)

#define BS_IMAGE(source_id, id, flags) BS_OBJECT(bs_Image, source_id, id, BS_SWAPS_COUNT(flags), flags)
#define BS_SAMPLER(source_id, id, flags) BS_OBJECT(bs_Sampler, source_id, id, BS_SWAPS_COUNT(flags), flags)
#define BS_RENDERER(source_id, id, flags) BS_OBJECT(bs_Renderer, source_id, id, BS_SWAPS_COUNT(flags), flags)
#define BS_BATCH(source_id, id, flags) BS_OBJECT(bs_Batch, source_id, id, BS_SWAPS_COUNT(flags), flags)
#define BS_QUEUE(source_id, id, flags) BS_OBJECT(bs_Queue, source_id, id, BS_SWAPS_COUNT(flags), flags)
#define BS_BUFFER(source_id, id, flags) BS_OBJECT(bs_Buffer, source_id, id, BS_SWAPS_COUNT(flags), flags)
#define BS_PIPELINE(source_id, id, flags) BS_OBJECT(bs_Pipeline, source_id, id, BS_SWAPS_COUNT(flags), flags)
#define BS_RAY_TRACER(source_id, id, flags) BS_OBJECT(bs_RayTracer, source_id, id, BS_SWAPS_COUNT(flags), flags)
#define BS_ATLAS(source_id, id, flags) BS_OBJECT(bs_Atlas, source_id, id, BS_SWAPS_COUNT(flags), flags)
#define BS_FONT(source_id, id, flags) BS_OBJECT(bs_Font, source_id, id, BS_SWAPS_COUNT(flags), flags)

   /**
    Amount of scene loads the engine will perform before destroying unloaded objects
    */
    #define BS_NUM_STRIKES_RULE (1)



  /*==============================================================================
   * Interface
   *============================================================================*/

    extern bs_List bs_resources;

#define BS_QUERY_FORCE_CREATE (1 << 31)
#define BS_QUERY_ALLOW_NULL (1 << 30)
#define BS_QUERY_MODEL_KEEP_JSON (1 << 29)

    BSAPI bs_List* bs_packages();
    BSAPI bs_List* bs_objectSources();
    BSAPI void bs_destroyResource(bs_Resource* resource);
    BSAPI bs_Resource* bs_queryResource(int package_id, const char* name);
    BSAPI int bs_queryPackage(const char* name);
    BSAPI bs_Resource* bs_loadResource(int package_id, const char* resource_name, bs_U32 flags);
    BSAPI int bs_loadPackage(const char* path);

    BSAPI int bs_configureSource(bs_ObjectType type, int count, const char** names);

   /**
    @param source_id
    @param id
    @returns True if the object at the specified id has been created, otherwise false
    */
    BSAPI bool
    bs_exists(
        bs_U32 source_id, 
        bs_U32 id);

   /**
    @param source_id
    @param id
    @returns Object at the specified id
    @throws BSX_DOESNT_EXIST - Object has not yet been created 
    */
    BSAPI bs_Object*
    bs_fetch(
        bs_U32 source_id,
        bs_U32 id);

    BSAPI bool 
    bs_shouldLoadId(
        bs_U32 source_id, 
        bs_U32 id);

#endif