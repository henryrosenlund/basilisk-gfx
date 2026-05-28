#include <bsgfx.h>
#include <bsmod_compile.h>
#include <bsmod_bpak.h>
#include <bsmod.h>
#include <bs_json.h>
#include <bs_window.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    int id;
    int x, y;
    int width, height;
    int x_offset, y_offset;
    int x_advance;
} BMChar;

typedef struct {
    int first;
    int second;
    int amount;
} BMKerning;

typedef struct {
    int size;

    BMChar* chars;
    int char_count;

    BMKerning* kerning_pairs;
    int kerning_pairs_count;

    int line_height;
    int base;
} BMFont;

static void bsmod_parseCharLine(const char* line, BMChar* c) {
    sscanf(line, "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d", &c->id, &c->x, &c->y, &c->width, &c->height, &c->x_offset, &c->y_offset, &c->x_advance);
}

static void bsmod_parseKerningLine(const char* line, BMKerning* k) {
    sscanf(line, "kerning first=%d second=%d amount=%d", &k->first, &k->second, &k->amount);
}

static BMFont loadBMFont(const char* path) {
    BMFont font = { 0 };

    FILE* f = fopen(path, "r");
    if (!f)
        return font;

    char line[512];
    int charIdx = 0;
    int kernIdx = 0;

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "info ", 5) == 0) {
            sscanf(line, "info face=%*[^ ] size=%d", &font.size);
        }
        else if (strncmp(line, "common ", 7) == 0) {
            sscanf(line, "common lineHeight=%d base=%d", &font.line_height, &font.base);
        }
        else if (strncmp(line, "chars count=", 12) == 0) {
            sscanf(line, "chars count=%d", &font.char_count);
            font.chars = calloc(font.char_count, sizeof(BMChar));
        }
        else if (strncmp(line, "kernings count=", 15) == 0) {
            sscanf(line, "kernings count=%d", &font.kerning_pairs_count);
            font.kerning_pairs = calloc(font.kerning_pairs_count, sizeof(BMKerning));
        }
        else if (strncmp(line, "char ", 5) == 0)
            bsmod_parseCharLine(line, &font.chars[charIdx++]);
        else if (strncmp(line, "kerning ", 8) == 0)
            bsmod_parseKerningLine(line, &font.kerning_pairs[kernIdx++]);
    }

    fclose(f);
    return font;
}

void bsmod_packBMFont(char* package_name, char* bmfont_path, char* png_path, char* format, ...) {
    int width = 0, height = 0;
    const int channels_count = 4;

    BMFont font = loadBMFont(bmfont_path);
    unsigned char* bmp = bs_loadPng(png_path, &width, &height, channels_count);

    const size_t bfnt_size = sizeof(bs_BfntHeader) + sizeof(bs_BfntKerningPair) * font.kerning_pairs_count + sizeof(bs_BfntGlyph) * font.char_count;
    const size_t batl_size = sizeof(bs_BatlHeader) + (sizeof(bs_BatlPointer) + sizeof("\n")) * font.char_count;

    bs_BfntHeader header = {
        .magic = 0x746E6662,
        .version = 1,
        .kerning_pairs_count = font.kerning_pairs_count,
        .glyphs_count = font.char_count,
        .line_height = font.line_height,
        .units_per_em = font.line_height, // good?
        .size = font.size,
        .batl_offset = bfnt_size,
    };

    const size_t total_size_excluding_binary = bfnt_size + batl_size;
    const size_t atlas_size = width * height * channels_count;
    const size_t total_size = total_size_excluding_binary + atlas_size;

    unsigned char* bfnt = bs_malloc(total_size);
    unsigned char* offset = bfnt + sizeof(bs_BfntHeader);

    for (int i = 0; i < font.kerning_pairs_count; i++) {
        bs_BfntKerningPair* pair = offset;
        pair->right = font.kerning_pairs[i].second;
        pair->value = font.kerning_pairs[i].amount;

        offset += sizeof(bs_BfntKerningPair);
    }

    for (int i = 0; i < font.char_count; i++) {
        bs_BfntGlyph* glyph = offset;
        BMChar* g = &font.chars[i];
        int code = g->id;
        if (code < 256)
            header.ascii_table[code] = i;

        *glyph = (bs_BfntGlyph) {
            .code = code,
            .y_offset = font.base - (g->y_offset + g->height),
            .advance_width = g->x_advance,
            .left_side_bearing = g->x_offset,
            .kerning_pair_offset = 0,
            .kerning_pair_count = 0,
        };

        offset += sizeof(bs_BfntGlyph);
    }

   /**
    Atlas
    */
    bs_BatlHeader* batl_header = offset;
    *batl_header = (bs_BatlHeader) {
        .magic = 0x6C746162,
        .version = 1,
        .binary_offset = batl_size,
        .width = width,
        .height = height,
        .channels_count = channels_count,
        .images_count = font.char_count,
    };
    offset += sizeof(bs_BatlHeader);

    for (int i = 0; i < font.char_count; i++) {
        bs_BatlPointer* p = offset;
        BMChar* g = &font.chars[i];

        *p = (bs_BatlPointer){
            .x = g->x,
            .y = g->y,
            .w = g->width,
            .h = g->height,
        };

        offset += sizeof(bs_BatlPointer) + sizeof("\n");
    }

    assert((total_size - (offset - bfnt)) == atlas_size);
    memcpy(offset, bmp, atlas_size);
    memcpy(bfnt, &header, sizeof(bs_BfntHeader));

    va_list args;
    va_start(args, format);
    bsmod_packResourceV(BS_RESOURCE_FONT, bfnt, total_size, package_name, format, args);
    va_end(args);

    free(font.kerning_pairs);
    free(font.chars);
    bs_free(bfnt);
}