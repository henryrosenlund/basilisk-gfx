#ifndef BSMOD_BMFONT_H
#define BSMOD_BMFONT_H

#include <bs_types.h>

void 
bsmod_packBMFont(
	char* package_name, 
	char* bmfont_path, 
	char* png_path,
	char* resource_name_format,
	...);

#endif