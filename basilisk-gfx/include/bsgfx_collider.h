
 /**
  bsgfx_collider.h
  */

#ifndef BSGFX_COLLIDER_H
#define BSGFX_COLLIDER_H

#include <bs_types.h>
#include <spawners/entity/bsgfx_entity.h>
#include "../bsgfx_contracts.h"



  /*==============================================================================
   * Macros 
   =============================================================================*/

	#define BSGFX_COLLIDER_SKIN (0.015)



  /*==============================================================================
   * Enums
	=============================================================================*/

	typedef bs_U32 bsgfx_ColliderFlags;
	typedef enum {
		BSGFX_COLLISION_NONE				= 0,
		BSGFX_COLLISION_SLOPE				= 1 << 0,
		BSGFX_COLLISION_SLOPE_DESCENT		= 1 << 1,
		BSGFX_COLLISION_ABOVE				= 1 << 2,
		BSGFX_COLLISION_BELOW				= 1 << 3,
		BSGFX_COLLISION_LEFT				= 1 << 4,
		BSGFX_COLLISION_RIGHT				= 1 << 5,
		BSGFX_COLLISION_BACK				= 1 << 6,
		BSGFX_COLLISION_FRONT				= 1 << 7,
		BSGFX_COLLISION_MAX_SLOPE			= 1 << 8,

		BSGFX_COLLISION_STAIRS				= 1 << 9,
	};



  /*==============================================================================
   * Structures
   =============================================================================*/

	typedef struct {
		bsgfx_ColliderFlags collision;
		bs_U32 batch_offset;
		bs_vec3 velocity_old;
		bs_vec3 normal; // normal of the current surface
		float angle; // angle of the current surface (radians)
		float angle_old;
		float length;
		float sweep_radius;
		bs_ivec3 resolution;
		bs_vec3 scale;
		// bs_ivec3 direction; // collision direction
		bs_Aabb aabb;
		bool active;
	} bsgfx_Collider;

	typedef struct {
		bs_vec3 position;
		bs_vec4 rotation;
		bs_vec3 scale;
		bs_U32 flags;
	} bsgfx_SweepCollision;



  /*==============================================================================
   * Interface
   =============================================================================*/

	BSGFXAPI void bsgfx_sweepCollisions(float sweep_radius, bs_vec3 position);

	BSGFXAPI bsgfx_Collider
	bsgfx_collider(
		bs_Aabb aabb,
		bs_vec3 scale,
		bs_ivec3 resolution,
		float sweep_radius);

	BSGFXAPI void
	bsgfx_applyCollisions(
		bsgfx_Collider* collider, 
		bs_vec3 position, 
		bs_vec3* velocity);

	#ifdef _DEBUG

	BSGFXAPI void
	bsgfx_printCollisions(
		bsgfx_Collider* collider);

	BSGFXAPI void
	bsgfx_instanceSweepCollisions();

	BSGFXAPI void
	bsgfx_instanceCollider(
		bsgfx_Collider* collider,
		bs_vec3 position,
		bs_vec3* velocity);

	#endif

#endif