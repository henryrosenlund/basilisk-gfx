#ifndef BSMOD_ATLAS_H
#define BSMOD_ATLAS_H

typedef struct {
	bs_List info;
	bs_List rects;
} bsmod_AtlasPacker;

typedef struct {
	char* name;
	bs_RGBA* data;
	int name_length;
	int category;
} bsmod_TextureInfo;

void 
bsmod_packAtlasTexture(
	bsmod_AtlasPacker* packer, 
	char* name, 
	bs_RGBA* data, 
	int width, 
	int height,
	int category);

void 
bsmod_packAtlas(
	bsmod_AtlasPacker* packer, 
	int width, 
	int height, 
	char* package, 
	char* resource_name);

bsmod_AtlasPacker 
bsmod_createAtlasPacker();

#endif