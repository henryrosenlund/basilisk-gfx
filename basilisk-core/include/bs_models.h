
 /**
  bs_models.h
  Models, armatures, animations
  */

#ifndef BS_MODELS_H
#define BS_MODELS_H

#include <bs_types.h>



 /*==============================================================================
  * Models
  *============================================================================*/

    BSAPI bs_Resource*
    bs_model(
        int package_id, 
        const char* name, 
        bs_U32 flags);

    BSAPI void 
    bs_destroyModel(
        bs_Model* model);



 /*==============================================================================
  * Animations
  *============================================================================*/

    BSAPI bs_vec4 
    bs_interpolateRotation(
        bs_AnimationBone* animation_joint, 
        float time);

    BSAPI bs_vec3 
    bs_interpolateTranslation(
        bs_AnimationBone* animation_joint, 
        float time);

    BSAPI bs_vec3 
    bs_interpolateScale(
        bs_AnimationBone* animation_joint, 
        float time);

   /**
    Get the transformation of a bone from the armature's current pose
    @param armature
    @param bone
    @returns 4x4 matrix representing the bone's transformation
    */
    BSAPI bs_mat4 
    bs_boneTransform(
        bs_Armature* armature, 
        bs_Bone* bone);

   /**
    Get the local position of a bone from the armature's current pose
    @param armature
    @param bone
    @returns Position of the bone
    */
    BSAPI bs_vec3 
    bs_bonePosition(
        bs_Armature* armature, 
        bs_Bone* bone);

    BSAPI bs_mat4*
    bs_transformBone(
        bs_Armature* armature,
        bs_Bone* bone,
        bs_mat4 transform);

   /**
    Sets the armature pose to an interpolation between two animations
    @param armature
    @param animation_a - First animation
    @param animation_b - Second animation, can be NULL to skip blending
    @param factor - Amount to blend between 0 and 1
    @param time_a - The time in seconds at which to sample from the first animation
    @param time_b - The time in seconds at which to sample from the second animation
    */
    BSAPI void 
    bs_blendPose(
        bs_Armature* armature, 
        bs_Animation* animation_a, 
        bs_Animation* animation_b, 
        float factor,
        float time_a,
        float time_b);



   /*==============================================================================
    * Armature
    *============================================================================*/

    /*
    BSAPI bs_Object
    bs_armature(
        int id, 
        bs_ArmatureFlags flags);
        */
    BSAPI int 
    bs_bone(
        bs_Armature* armature, 
        bs_mat4 local_transform, 
        int parent_id, 
        const char* name);

  //  bs_Object
  //  bs_animation(
  //      bs_Armature* armature,
  //      int id,
  //      const char* name,
  //      bs_AnimationFlags flags);

    BSAPI void
    bs_fabrik(
        bs_Armature* armature,
        int end_effector_id,
        bs_vec3 target,
        int chain_length,
        float* chain);

   /**
    Sets the armature's pose to its bind pose/T pose
    @param armature
    */
    BSAPI void
    bs_bindPose(
        bs_Armature* armature);

    BSAPI void 
    bs_keyframePosition(
        bs_AnimationBone* bone, 
        float timestamp, 
        bs_vec3 position);

    BSAPI void 
    bs_keyframeRotation(
        bs_AnimationBone* bone, 
        float timestamp, 
        bs_vec4 rotation);

    BSAPI void 
    bs_keyframeScale(
        bs_AnimationBone* bone, 
        float timestamp, 
        bs_vec3 scale);

    BSAPI bs_Animation 
    bs_loadAnimation(
        bs_Model* model, 
        const char* name);



  /*==============================================================================
   * Queries
   *============================================================================*/

  /**
   Find a model's animation by its name
   @param model
   @param id - Object id the animation will be assigned to
   @param name
   @param flags
   @returns Object containing the created animation
   @throws BSX_FAILED_TO_QUERY - The animation could not be found
   */
    //bs_Object
    //bs_queryAnimation(
    //    bs_Model* model,
    //    int id,
    //    const char* name, 
    //    bs_AnimationFlags flags);

    // todo docs
    BSAPI int
    bs_queryBoneId(
        bs_Armature* armature,
        const char* name);

    BSAPI bs_Armature*
    bs_queryArmature(
        bs_Model* model,
        const char* name);

   /**
    Find a bone in an armature by its name
    @param armature
    @param name
    @returns Pointer to the bone that was found
    @throws BSX_FAILED_TO_QUERY - The bone could not be found
    */
    BSAPI bs_Bone* 
    bs_queryBone(
        bs_Armature* armature, 
        const char* name);

   /**
    Find a model's armature by its name
    @param model
    @param id - Object id the armature will be assigned to
    @param name
    @param flags
    @returns Object containing the created armature
    @throws BSX_FAILED_TO_QUERY - The armature could not be found
    */
    /*
    BSAPI bs_Object
    bs_queryArmature(
        bs_Model* model, 
        int id,
        const char* name, 
        bs_ArmatureFlags flags);
    */

   /**
    Find model's mesh by its name
    @param model
    @param name
    @returns Pointer to the mesh that was found
    @throws BSX_FAILED_TO_QUERY - The mesh could not be found
    */
    BSAPI bs_Mesh* 
    bs_queryMesh(
        bs_Model* model, 
        const char *name);

    BSAPI bs_Mesh* bs_queryMeshHash(bs_Model* model, bs_U64 hash, const char* name);

    BSAPI bs_Material*
    bs_queryMaterial(
        bs_Model* model,
        const char* name);

#endif