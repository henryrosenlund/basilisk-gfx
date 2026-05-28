#include <bsgfx.h>
#include <UI/bsgfx_ui.h>
#include <bsgfx_instance.h>
#include <bsgfx_material.h>

#include <bsmod.h>

void bsmod_saveHistory(bsgfx_TypeId type_id) {
    //    bsgfx_Type* type = bsgfx_types + type_id;
    //    if (!type->count)
    //        return;
    //
    //    char appdata[MAX_PATH];
    //    bs_appdataPath(appdata);
    //
    //    bs_DateTime time = bs_dateTime();
    //    bs_I64 seconds = bs_totalSeconds(&time);
    //
    //    bs_String* name = bs_stringF(NULL, "%s/.voc/history/%s_%ld.bin", appdata, type->plural, seconds); // todo get game name
    //
    //    bs_ensureDirectory(name->value);
    //    bs_saveFile(name->value, type->list, *type->count * type->type_size);
    //
    //    bs_free(name);
}

static void bsmod_findClosestHistory(bs_FileInfo info, struct { bsgfx_TypeId previous_type, next_type; bs_I64 previous, next; } *params) {
    info.path = bs_fileName(info.path);

    char* date_start = strchr(info.path, '_');
    assert(date_start);
    char* end = strchr(info.path, '.');
    assert(end);

    end[0] = '\0'; // hack to skip alloc
    date_start[0] = '\0';

    bs_I64 time = bs_toLong(date_start + 1);
    bsgfx_TypeId type = bsmod_queryType(info.path);

    end[0] = '.';
    date_start[0] = '\0';

    if (time != 0) {
        if (time - bsmod.history > 0) {
            params->next = BS_MIN(params->next, time);
            params->next_type = type;
        }
        else if (time - bsmod.history < 0) {
            params->previous = BS_MAX(params->previous, time);
            params->previous_type = type;
        }
    }
}

void bsmod_loadPreviousHistory() {
    char* appdata = bs_appdataPath(appdata);

    struct { bsgfx_TypeId previous_type, next_type; bs_I64 previous, next; } params = {
        .previous = 0,
        .next = 0,
    };

    bs_foreachFileF(
        bsmod_findClosestHistory,
        &params,
        "%s/.woc/history", // todo get game name
        appdata);

    if (params.previous != 0) {
        if (bsmod.history == BS_I64_MAX)
            bsmod_saveHistory(params.previous_type);

        bsmod.history = params.previous;
        //bsmod_queueLoadType(params.previous_type);
    }
}

void bsmod_loadNextHistory() {
    if (bsmod.history == BS_I64_MAX)
        return;

    char* appdata = bs_appdataPath(appdata);

    struct { bsgfx_TypeId previous_type, next_type; bs_I64 previous, next; } params = {
        .previous = 0,
        .next = BS_I64_MAX,
    };

    bs_foreachFileF(
        bsmod_findClosestHistory,
        &params,
        "%s/.woc/history", // todo get game name
        appdata);

    if (params.next != BS_I64_MAX) {
        bsmod.history = params.next;
        //bsmod_queueLoadType(params.next_type);
    }
}