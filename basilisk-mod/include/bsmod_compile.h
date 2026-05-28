#ifndef BSMOD_COMPILE_H
#define BSMOD_COMPILE_H

#include <bsmod.h>

void bsmod_loadShaderReferences();

void bsmod_updateShaderReferences();
void 
bsmod_iniCompiler();
BSMODAPI bs_Result bsmod_compileShader(
	char* path,
	char* name,
	char* package);
void bsmod_updateBindings();

#endif