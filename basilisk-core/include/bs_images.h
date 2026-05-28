 
 /**
  bs_images.h
  Images and samplers
  */

#ifndef BS_IMAGES_H
#define BS_IMAGES_H

#include <bs_types.h>



  /*==============================================================================
   * Images
   *============================================================================*/

   /**
    @param object
    @param resolution - Image size in pixels
    @param num_indices - Amount of array indices, or 0 if its not an image array 
    @param format
    @param flags
    @returns
    */
    BSAPI bs_Result
    bs_image(
        bs_Object* object,
        bs_ivec2 dim,
        int num_indices,
        bs_Format format,
        bs_U32 flags);

    BSAPI int bs_imageSwapsCount(bs_Image* image);

   /**
    Change the image layout
    @param image
    @param index - Array index of the image that will be transitioned
    @param old_layout - Layout the image is currently in
    @param new_layout - Layout the image should be
    @throws BSX_UNKNOWN_LAYOUT_TRANSITION - Transition between old and new layout doesn't exist
    */
    BSAPI void
    bs_transition(
        bs_Image* image,
        int index,
        bs_ImageLayout old_layout,
        bs_ImageLayout new_layout);

   /**
    @param path - Path to the PNG file
    @param width - Pointer to an integer where the image width will be stored
    @param height - Pointer to an integer where the image height will be stored
    @param out_size
    @returns Pointer to the file data
    @throws BSX_GENERAL - lodepng failure
    */
    BSAPI unsigned char*
    bs_inspectPng(
        const char* path, 
        int* width, 
        int* height,
        size_t* out_size);

    BSAPI unsigned char* 
    bs_loadPngMemory(
        char* data, 
        size_t size, 
        int* width, 
        int* height, 
        int channels_count);

   /**
    @param path - Path to the PNG file
    @param width - Pointer to an integer where the image width will be stored
    @param height - Pointer to an integer where the image height will be stored
    @param channels_count - Amount of channels the image has, must be either 3 (RGB) or 4 (RGBA)
    @returns Pointer to the image data
    @throws BSX_INVALID_TYPE - channels_count is not 3 or 4
    @throws BSX_GENERAL - lodepng failure
    */
    BSAPI unsigned char*
    bs_loadPng(
        const char* path,
        int* width,
        int* height,
        int channels_count);

    BSAPI bs_Result
    bs_bitmapImage(
        bs_Object* existing_object, 
        unsigned char* image_data, 
        bs_ivec2 dim, 
        bs_Format format, 
        bs_ImageBits flags);

   /**
    Save a bitmap as a PNG file
    @param data - Pointer to bitmap data
    @param alpha - Whether the image has transparency or not
    @param resolution - Size of the image in pixels
    @param name - Path where the file will be saved
    */
    BSAPI void
    bs_savePng(
        char* data,
        bs_ivec2 resolution,
        bs_PngType type,
        const char* name);

    BSAPI unsigned char*
    bs_encodePng(
        size_t* out_size, 
        const unsigned char* data, 
        bs_ivec2 size, 
        bs_PngType type);

   /**
    Save a bitmap as a PNG file
    @param data - Pointer to bitmap data
    @param alpha - Whether the image has transparency or not
    @param resolution - Size of the image in pixels
    @param format - Format path where the file will be saved
    @param ...
    */
    BSAPI void
    bs_savePngF(
        char* data,
        bs_ivec2 resolution,
        bs_PngType type,
        const char* format,
        ...);


   /**
    Deallocate an image and all of its resources
    @param image
    */
    BSAPI void
    bs_destroyImage(
        bs_Image* image);

   /**
    Resize an image, this will destroy and recreate the image
    @param image
    @param resolution - Size of the image in pixels
    @param num_indices - Amount of array indices, or 0 if its not an image array
    */
    BSAPI void
    bs_resizeImage(
        bs_Image* image,
        bs_ivec2 resolution,
        int num_indices);

    BSAPI int 
    bs_queryImageIndexHash(
        bs_Image* image, 
        bs_U64 name_hash, 
        char* name);

    BSAPI int 
    bs_queryImageIndex(
        bs_Image* image, 
        char* name);

   /**
    Copy image data to a buffer
    @param image
    @param buffer
    @param image_index - Image array index, 0 if the image is not an array
    @param layout - Image layout the image is currently in
    @param buffer_offset - Offset in bytes to start copying into
    @param offset - Offset in pixels to start copying from
    @param resolution - Size of the image in pixels
    @throws BSX_OUT_OF_BOUNDS - Image offset is too big
    @throws BSX_OUT_OF_BOUNDS - Buffer size is too small
    @returns Error that was thrown
    */
    BSAPI void
    bs_copyImageToBufferAsync(
        bs_Image* image,
        bs_Buffer* buffer,
        int image_index,
        bs_ImageLayout layout,
        bs_U64 buffer_offset,
        bs_ivec2 offset,
        bs_ivec2 resolution);

   /**
    Copy buffer data to an image
    @param buffer
    @param image
    @param index - Array index of the image to copy
    @param layout - Image layout the image is currently in
    */
    BSAPI void
    bs_copyBufferToImage(
        bs_Buffer* buffer,
        bs_Image* image,
        int index,
        bs_ImageLayout layout);

    BSAPI void
    bs_blit(
        bs_BlitOperation operation);

    BSAPI bs_Object* 
    bs_loadImage(
        bs_Object* object, 
        int package_id, 
        char* resource_name, 
        bs_ImageBits flags);

   /**
    @param format
    @returns true if the format is a depth/stencil format, otherwise false
    */
    BSAPI bool
    bs_isStencilFormat(
        bs_Format format);

   /**
    @param format
    @returns true if the format is a depth format, otherwise false
    */
    BSAPI bool
    bs_isDepthFormat(
        bs_Format format);

   /**
    @param format
    @returns true if the format has an alpha component, otherwise false
    */
    BSAPI bool
    bs_hasAlpha(
        bs_Format format);

    BSAPI void 
    bs_nameImage(
        bs_Image* image, 
        const char* name);



  /*==============================================================================
   * Sampler
   *============================================================================*/

    BSAPI void 
    bs_destroySampler(
        bs_Sampler* sampler);

   /**
    @param id - Object id the sampler will be assigned to
    @param filter
    @param flags
    @returns Object containing the created sampler
    */
    BSAPI bs_Object*
    bs_sampler(
        bs_Object* object,
        bs_ImageFilter filter,
        bs_SamplerBits flags);



  /*==============================================================================
   * Atlas
   *============================================================================*/

    BSAPI bs_Object* 
    bs_loadAtlas(
        int id, 
        int package_id, 
        const char* resource_name, 
        bs_U32 flags);

    BSAPI bs_vec4 
    bs_atlasCoordinates(
        bs_Atlas* atlas, 
        int texture_id, 
        int frame);

    BSAPI bs_vec4 
    bs_mirrorUV(
        bs_vec4 uv);

    BSAPI bs_vec4 
    bs_flipUV(
        bs_vec4 uv);

    BSAPI bs_vec2 
    bs_atlasSize(
        bs_Atlas* atlas, 
        int texture);

    BSAPI int 
    bs_queryAtlasHash(
        bs_Atlas* atlas, 
        bs_U64 hash, 
        const char* name);

    BSAPI int 
    bs_queryAtlas(
        bs_Atlas* atlas, 
        const char* name);

    BSAPI void 
    bs_destroyAtlas(
        bs_Atlas* atlas);

    BSAPI void 
    bs_splitAtlasTexture(
        bs_Atlas* atlas, 
        char* name, 
        int split);

    BSAPI bs_Object* 
    bs_loadAtlasMemory(
        bs_Object* object, 
        int package_id, 
        char* resource_name, 
        char* data,
        bs_U32 flags);

    BSAPI bs_Object*
    bs_loadAtlas(
        bs_Object* object,
        int package_id, 
        const char* resource_name, 
        bs_U32 flags);

#endif