
 /**
  bsgfx_item.c
  */

#include <bs_collision.h>
#include <bs_physics.h>
#include <bs_log.h>

#include <bsgfx_cache.h>
#include <bsgfx_collider.h>

#include <spawners/item/bsgfx_item.h>

bs_List bsgfx_items = { .unit_size = sizeof(bsgfx_Item) };



  /*==============================================================================
   * Physics
   *============================================================================*/

static void bsgfx_applyPhysics(bsgfx_Item* item) {
	bs_throwBasilisk(BSX_NOT_IMPLEMENTED);
	/*
	bs_Model* model = $items();
	bs_Mesh* mesh = model->meshes + item->mesh;
	bs_Simulation* sim = &item->simulation;

	bs_applyGravityForce(sim, 1.0);
	//bs_applyDragForce(sim);
	bs_mat4 physics_result = bs_applyIntegration(sim);
	bs_Box box = {
		.extent = bs_aabbExtent(&mesh->aabb),
		.transform = &physics_result,
	};

	bsgfx_sweepCollisions(8.0, item->simulation.position);

	static bs_List contacts = { .unit_size = sizeof(bs_Contact) };
	contacts.count = 0;

	for (int i = 0; i < _poser->sweep_collisions.count; i++) {
		bsgfx_SweepCollision* sweep = bs_fetchUnit(&_poser->sweep_collisions, i);
		bs_mat4 transform = bs_transform(sweep->position, sweep->rotation, bs_v3(1, 1, 1));
		bs_Box against = {
			.transform = &transform,
			.extent = sweep->scale,
		};

		bs_Contact* insert = bs_pushBack(&contacts, NULL);
		contacts.count -= !bs_boxVsBox(&box, sim, &against, NULL, insert);
	}

	if (contacts.count != 0) {
		bs_presolveContacts(contacts.data, contacts.count);
		bs_resolveInterpenetrations(contacts.data, contacts.count);
		bs_resolveVelocities(contacts.data, contacts.count);
	}
	*/
}



  /*==============================================================================
   * Instancing
   *============================================================================*/

void bsgfx_instanceItem(bsgfx_Item* item, bs_mat4 transform, int material) {
	bs_throwBasilisk(BSX_NOT_IMPLEMENTED);

	/*
	bs_Model* model = $items();
	bs_Mesh* mesh = model->meshes + item->mesh;

	int subtype = *(int*)mesh->extra;

	const bsgfx_MeshInstance instance = {
		.transform = transform,
	};

	bsgfx_meshInstance(subtype, &instance, 0, 0, material);
	*/
}

void bsgfx_instanceItems() {
	bs_throwBasilisk(BSX_NOT_IMPLEMENTED);
	/*
	bs_Model* model = $items();
	for (int i = 0; i < bsgfx_items.count; i++) {
		bsgfx_Item* item = bs_fetchUnit(&bsgfx_items, i);
		bs_mat4 transform = bs_transform(item->simulation.position, item->simulation.rotation, bs_v3(1, 1, 1));
		bsgfx_instanceItem(item, transform, item->material_id);

		bs_Mesh* mesh = model->meshes + item->mesh;
		bs_Aabb aabb = {
			.min = bs_v3(-1, -1, -1),
			.max = bs_v3(1, 1, 1),
		};
		bsgfx_obbInstance(&mesh->aabb, BS_WHITE, &transform);
	}
	*/
}

void bsgfx_tickItems() {
	for (int i = 0; i < bsgfx_items.count; i++) {
		bsgfx_Item* item = bs_fetchUnit(&bsgfx_items, i);
		bsgfx_applyPhysics(item);
	}
}



  /*==============================================================================
   * Interface
   *============================================================================*/

void bsgfx_loadItems() {
	if (bs_exists(BSGFX_BATCH_ITEMS))
		return;

	bs_U32 model_flags = 0, batch_flags = 0;
#ifdef _DEBUG
	model_flags = BS_MODEL_FORCE_DESTROY;
	batch_flags = BS_BATCH_FORCE_DESTROY;
#endif

	bs_throwBasilisk(BSX_NOT_IMPLEMENTED);

	/*
	//bs_Model* model = bs_model(BSGFX_MODEL_ITEMS, "resources/items.gltf", model_flags);
	bs_Model* model = $items();
	bs_Shader* shader = $vs_bsgfx_mesh_instanced();
	//bs_Batch* batch = bs_batch(BSGFX_BATCH_ITEMS, sizeof(int), shader, batch_flags).batch;
	bs_except(BSX_NOT_FOUND);
	bs_Batch* volume_batch = bs_fetch(BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED).batch;
	if (bs_except(BSX_NOT_FOUND))
		return;
	bs_Batch* batch = bs_fetch(BSGFX_BATCH_MESH_INSTANCED).batch;
	if (bs_except(0))
		return;
	if (!bs_batchIsPushed(batch)) {
		static int* cached_subtypes;

		if (!cached_subtypes) {
			cached_subtypes = bs_malloc(model->meshes_count * BSGFX_ITEM_SUBTYPE_COUNT * sizeof(int));
			memset(cached_subtypes, -1, model->meshes_count * BSGFX_ITEM_SUBTYPE_COUNT * sizeof(int));
			for (int i = 0; i < model->meshes_count; i++) {
				bs_Mesh* mesh = model->meshes + i;
				bs_Range range = bs_pushMesh(batch, mesh);

				cached_subtypes[i * BSGFX_ITEM_SUBTYPE_COUNT + BSGFX_ITEM_SUBTYPE] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, BSGFX_BATCH_MESH_INSTANCED, BSGFX_SUBTYPE_HAS_SHADOWS, range);
				cached_subtypes[i * BSGFX_ITEM_SUBTYPE_COUNT + BSGFX_ITEM_SUBTYPE_HI_RES_SCREEN] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, BSGFX_BATCH_MESH_INSTANCED, BSGFX_SUBTYPE_HAS_SHADOWS, range);
				cached_subtypes[i * BSGFX_ITEM_SUBTYPE_COUNT + BSGFX_ITEM_SUBTYPE_VOLUME] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED, 0, (bs_Range) { .batch = volume_batch });
				mesh->extra = cached_subtypes + i * BSGFX_ITEM_SUBTYPE_COUNT;
			}
		}
	}

	bs_infoF("Loaded %d items\n", model->meshes_count);
	*/
}

int bsgfx_closestItem(bs_vec3 position, float radius) {
	bs_throwBasilisk(BSX_NOT_IMPLEMENTED);
	/*
	bs_Model* model = $items();
	float closest = BS_FLT_MAX;
	int closest_i = -1;

	for (int i = 0; i < bsgfx_items.count; i++) {
		bsgfx_Item* item = bs_fetchUnit(&bsgfx_items, i);
		bs_Mesh* mesh = model->meshes + item->mesh;
		bs_vec3 box_center = bs_aabbCenter(&mesh->aabb);

		float distance = 0.0;
		if (bs_sphereVsBox(position, radius, bs_v3Add(item->simulation.position, box_center), item->simulation.rotation, bs_v3(1, 1, 1), NULL, NULL, &distance)) {
			closest_i = i;
			closest = BS_MIN(closest, distance);
		}
	}

	return closest_i;
	*/
}

void bsgfx_despawnAllItems() {
	bsgfx_items.count = 0;
}

void bsgfx_despawnItem(int id) {
	bs_infoF("Despawned item %d\n", id);

	for (int i = id; i < (bsgfx_items.count - 1); i++) {
		bsgfx_Item* this = bs_fetchUnit(&bsgfx_items, i),* next = bs_fetchUnit(&bsgfx_items, i + 1);
		*this = *next;
	}
	bsgfx_items.count--;
}

bsgfx_Item* bsgfx_spawnItem(int item, bs_vec3 position, float gravity, int material_id) {
	bs_throwBasilisk(BSX_NOT_IMPLEMENTED);
	/*
	bs_Model* model = $items();
	bs_Mesh* mesh = model->meshes + item;

	return bs_pushBack(&bsgfx_items, &(bsgfx_Item) {
		.simulation = bs_simulation(position, 50.0, 10.0, bs_m3Diag(bs_v3V1(30.0))),
		.mesh = item,
		.material_id = material_id,
	});
	*/
}

void bsgfx_renderItems(bs_Pipeline* pipeline, int key_start) {
	bs_throwBasilisk(BSX_NOT_IMPLEMENTED);
	/*
	bs_Model* model = $items();

	for (int i = 0; i < model->meshes_count; i++) {
		bs_Mesh* mesh = model->meshes + i;
		if (!mesh->extra)
			continue;
		int subtype = mesh->extra[key_start];
		bsgfx_renderSubtype(subtype, pipeline);
	}
	*/
}