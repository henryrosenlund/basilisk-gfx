#ifndef BSMOD_BPAK_H
#define BSMOD_BPAK_H

#include <bs_types.h>
#include <bsmod.h>

#define BSMOD_BPAK_CHUNK_SIZE 100'000'000

typedef struct {
	bs_List bin;
	int id;
	bool has_changes;
} bsmod_Chunk;

typedef struct {
	const char* name;
	bs_U64 name_hash;

	bs_List chunks;
	bs_List resources;

	bool has_changes;
} bsmod_Package;

typedef struct {
	bs_ResourceHeaderData header;
	char* name;
	bool has_changes;
	bs_ResourceType type;
} bsmod_Resource;

BSMODAPI bs_List*
bsmod_packages();

bsmod_Package* 
bsmod_queryPackage(
	const char* name);

BSMODAPI bsmod_Package*
bsmod_ensurePackage(
	const char* name);

BSMODAPI void 
bsmod_iniPackage(
	const char* package_name);

void
bsmod_packResourceV(
	bs_ResourceType type,
	unsigned char* data,
	size_t data_size,
	const char* package_name,
	const char* format,
	va_list args);

void
bsmod_packResourceF(
	bs_ResourceType type,
	unsigned char* data,
	size_t data_size,
	const char* package_name,
	const char* format,
	...);

void 
bsmod_packResource(
	bs_ResourceType type,
	unsigned char* data, 
	size_t data_size,
	const char* package_name,
	const char* resource_name);

BSMODAPI void 
bsmod_savePackage(
	const char* name);

#endif