#ifndef BSGFX_ANIMATOR_H
#define BSGFX_ANIMATOR_H

#include <bs_types.h>
#include <bs_window.h>
#include <bs_models.h>
#include <bs_mem.h>
#include "../bsgfx_contracts.h"

#include <spawners/entity/bsgfx_entity.h>

typedef enum bsgfx_Id bsgfx_Id;

enum {
    BSGFX_ANIMATOR_TYPE_ONCE_BIT = 1 << 0,
    BSGFX_ANIMATOR_TYPE_ONCE_PER_TICK_BIT = 1 << 1,
    BSGFX_ANIMATOR_TYPE_ONCE_PER_LOOP_BIT = 1 << 2,
    BSGFX_ANIMATOR_TYPE_ONCE_PER_EXIT_BIT = 1 << 3,
};

typedef struct {
    float time;
    float previous_time;
    float blend_factor;

    int queued_animation_id;
    int current_animation_id;
    int current_blend_animation_id;

    bs_Armature* armature;

    bs_U32 skeleton;

    bs_Animation* animations;
    int animations_count;

    void (*exit)();
} bsgfx_Animator;

#define du_animatorCallback(name) void(*##name)(bsgfx_Animator*)

BSGFXAPI int
bsgfx_skeleton(
    bs_Armature* armature);

BSGFXAPI int bsgfx_animationFrame(bs_Animation* animation, float time, int num_frames);
BSGFXAPI int bsgfx_animationFrameCount(bs_Animation* animation, float time_scale);

BSGFXAPI void 
bsgfx_applyAnimationVelocity(
    bsgfx_Animator* animator, 
    bs_vec3* velocity, 
    bs_vec2 input);

typedef struct {
    du_animatorCallback(once);
    du_animatorCallback(once_per_tick);
    du_animatorCallback(once_per_loop);
    du_animatorCallback(once_per_exit);
    du_animatorCallback(pose);
} bsgfx_AnimatorCallbacks;

BSGFXAPI void bsgfx_queueAnimation(bsgfx_Animator* animator, int animation_id);

BSGFXAPI void 
bsgfx_runAnimator(
    bsgfx_Animator* animator, 
    bsgfx_AnimatorCallbacks callbacks);

BSGFXAPI bsgfx_Animator
bsgfx_animator(
    bs_Armature* armature, 
    int resting_animation_id,
    int animations_count);

/*

void bsgfx_applyAnimationVelocity(bs_Armature* armature, bs_Animation* animation, bs_vec2 input);

BSGFXAPI void
bsgfx_setPose(
    int skeleton,
    bs_Armature* armature,
    bs_Animation* animation,
    float time);

BSGFXAPI void
bsgfx_runAnimator(
    bs_Model* model,
    bs_Armature* armature,
    char* table, 
    bsgfx_Entity* entity);

#define bsgfx_animatorCallback(name) void(*##name)(bsgfx_Animator*)

#define BSGFX_ANIMATION(id, on_once, on_tick, on_loop, on_exit, pose) \
    case id: bsgfx_runAnimator(animator, on_once, on_tick, on_loop, on_exit, pose); break

bsgfx_blendWith(bsgfx_Animator* animator, bs_Animation* animation, float factor) {
    animator->current_animation_blend = animation;
    animator->blend_factor = factor;
}

static inline int
bsgfx_animationFrame(bsgfx_Animator* animator, int num_frames) {
    bs_Animation* animation = bsgfx_animatorAnimation(animator);
    return animator->time / animation->length * (float)num_frames;
}

static inline void bsgfx_animateOnceDefault(bsgfx_Animator* animator) {
    animator->time = 0.0;
}

static inline void bsgfx_animateTickDefault(bsgfx_Animator* animator) {
    animator->time += bs_deltaTime();
}

static inline void bsgfx_animateLoopDefault(bsgfx_Animator* animator) {
    animator->time = 0.0;
}

static inline void bsgfx_animateExitDefault(bsgfx_Animator* animator) {
}

static inline void bsgfx_animatePoseDefault(bsgfx_Animator* animator) {
    bs_Animation* animation_a = animator->current_animation;
    bs_Animation* animation_b = animator->current_animation_blend;
    bs_Armature* armature = bs_fetch(animator->armature_id).armature;

    bs_blendPose(armature, animation_a, animation_b, animator->blend_factor, animator->time, animator->time);
}

BSGFXAPI void
bsgfx_runAnimator(
    bsgfx_Animator* animator,
    bsgfx_animatorCallback(once), 
    bsgfx_animatorCallback(once_per_tick), 
    bsgfx_animatorCallback(once_per_loop), 
    bsgfx_animatorCallback(once_per_exit),
    bsgfx_animatorCallback(pose));



BSGFXAPI void
bsgfx_animate(
    bsgfx_Id armature_id,
    bs_Animation* animation,
    float time,
    int joint_offset);

BSGFXAPI bsgfx_Animator
bsgfx_animator(
    bsgfx_Id armature_id,
    bs_Animation* resting_animation);

BSGFXAPI void
bsgfx_mapArmatureV(
    int skeleton_a, int skeleton_b, const bs_Armature* armature_a, bs_Armature* armature_b, bs_Animation* animation, float time, ...);
*/

#endif