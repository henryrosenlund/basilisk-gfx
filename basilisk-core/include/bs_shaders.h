 /**
  bs_shaders.h
  Shaders, bindings, pipelines
  */

#ifndef BS_SHADERS_H
#define BS_SHADERS_H

#include <stdbool.h>
#include <bs_types.h>



  /*==============================================================================
   * Shaders
   *============================================================================*/

	BSAPI bs_ShaderType bs_deserializeShaderType(const char* type_name);
	BSAPI const char* bs_serializeShaderType(bs_ShaderType type);


	BSAPI bs_Result
	bs_shader(
		int package_id, 
		const char* name, 
		bs_U32 flags,
		bs_Resource** out);

   /**
    Deallocate a shader and all its resources
	@param shader
    */
	BSAPI void
	bs_destroyShader(
		bs_Shader* shader);



  /*==============================================================================
   * Pipelines
   *============================================================================*/

	BSAPI bs_Pipeline*
	bs_computePipeline(
		bs_Shader* compute_shader,
		bs_PipelineFlags flags);

   /**
    Deallocate a compute shader and all of its resources
	@param pipeline
    */
	BSAPI void
	bs_destroyComputePipeline(
		bs_Pipeline* pipeline);

	BSAPI bs_Pipeline*
	bs_queryPipeline(
		bs_U64 hash);

	BSAPI bs_U64
	bs_pipelineHash(
		bs_PipelineHash* descriptor);

	BSAPI bs_Pipeline* 
	bs_pipeline(
		bs_PipelineHash* descriptor);

   /**
    Deallocate a pipeline and all of its resources
	@param pipeline
    */
	BSAPI void
	bs_destroyPipeline(
		bs_Pipeline* pipeline);

   /**
    Update the push constant for a pipeline

	Must be called right before rendering

	@param pipeline
	@param offset - Offset in bytes to start copying into
	@param size - Size in bytes to copy
	@param data - Pointer to the data to copy from

	@throws BSX_OUT_OF_BOUNDS - Push constant is smaller than the given size
    */
	BSAPI void
	bs_pushConstant(
		bs_Pipeline* pipeline,
		bs_U32 offset,
		bs_U32 size,
		void* data);

	BSAPI bs_Pipeline*
	bs_rayTracingPipeline(
		bs_RayTracePipelineHash* pipeline_hash);



  /*==============================================================================
   * Bindings
   *============================================================================*/

	BSAPI bs_BindType 
	bs_deserializeBindType(
		const char* string);

	BSAPI const char* 
	bs_serializeBindType(
		bs_BindType type);


	BSAPI void 
	bs_loadBindings(
		int package_id,
		const char* path);

	typedef struct {
		bs_Sampler* sampler;
		bs_Image* image;
		bs_ImageLayout layout;
	} bs_ImageDescriptor;

	
   /**
    Bind an image to the specified slots
	@param bind_set_slot - Slot between 0 and BS_MAX_NUM_BIND_SETS
	@param binding_slot - Slot between 0 and BS_MAX_NUM_BINDINGS
	@param image
	@param sampler
	@param layout - Image layout the image is currently in
    */
	BSAPI void 
	bs_bindImage(
		bs_U32 bind_set_slot, 
		bs_U32 binding_slot, 
		bs_Image* image, 
		bs_Sampler* sampler, 
		bs_ImageLayout layout);


	BSAPI void 
	bs_bindImages(
		bs_U32 bind_set_slot, 
		bs_U32 slot, 
		bs_ImageDescriptor* images,
		int images_count);

   /*
    Bind a buffer to the specified slots
	@param bind_set_slot
	@param binding_slot
	@param buffer
    */
	BSAPI void 
	bs_bindBuffer(
		bs_U32 bind_set_slot, 
		bs_U32 binding_slot,
		bs_Buffer* buffer);

	BSAPI void bs_bindAccelerationStructure(bs_U32 bind_set_slot, bs_U32 slot, bs_RayTracer* ray_tracer);

	// todo docs
	BSAPI void
	bs_pushDescriptors();

   /**
    Update bindings
    */
	BSAPI void
	bs_pushBindings();

	BSAPI bs_BindSet* bs_queryBindSet(bs_U32 id);

   /**
    @param bind_set
	@param binding_slot
	@returns Pointer to the binding at the given slot, or NULL if it wasn't found
    */
	BSAPI bs_Binding* bs_queryBinding(
		bs_BindSet* bind_set,
		bs_U32 id);

	BSAPI void 
	bs_configureAttribute(
		const char* name, 
		bs_Format base_format);

#endif