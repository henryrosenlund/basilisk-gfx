#ifndef BSMOD_RASTERIZE_H
#define BSMOD_RASTERIZE_H

#include <bs_types.h>

void
bsmod_queueRasterize(
	const char* package,
	const char* name,
	bs_Callback callback);

void
bsmod_pollRasterizer();

void 
bsmod_beginRasterize(
	bs_ivec2 render_size, 
	bs_ivec2 output_size);

void 
bsmod_endRasterize();

void 
bsmod_rasterizeInstance(
	bs_PipelineHash pipeline_hash, 
	int subtype,
	int instance_id,
	int category,
	char* name,
	int width, 
	int height,
	size_t push_constant_size,
	unsigned char* push_constant);

#endif