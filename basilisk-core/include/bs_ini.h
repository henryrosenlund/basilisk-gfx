
 /**
  bs_ini.h
  */

#ifndef BS_INI_H
#define BS_INI_H

#include <bs_types.h>
#include <windows.h>

#define BS_STRING_GEN_2(TYPE, FUNC, ...) { .size = sizeof(TYPE), .func = #FUNC, __VA_OPT__(.is_required = __VA_ARGS__) },


  /*==============================================================================
   * Ini
   *============================================================================*/

   /**
    Parse through Basilisk's known launch options, results are stored in bs_args
    @param argc
    @param argv
    */
    BSAPI void
    bs_parseArgs(
        int argc,
        char* argv[]);

    BSAPI bs_Args* bs_arguments();

   /**
    Create Vulkan objects
    */
    BSAPI void
    bs_ini();

    // todo better info
   /**
    Loads various resources
    @param load_resources
    */
    BSAPI void
    bs_load(
        bs_Callback load_resources);

    BSAPI void
    bs_queryProcedures(
        bs_Procedure* procedures,
        int count,
        HMODULE dll_handle,
        unsigned char* destination);

#endif
