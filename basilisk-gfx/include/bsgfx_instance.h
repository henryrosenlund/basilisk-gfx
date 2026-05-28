 
 /**
  bsgfx_instance.h
  System for Vulkan instancing
  */

#ifndef BSGFX_INSTANCE_H
#define BSGFX_INSTANCE_H

#include <bs_types.h>
#include <bs_math.h>
#include <bs_images.h>

#include <bsgfx_scene.h>
#include <../bsgfx_contracts.h>

#include <assert.h>



   /*==============================================================================
    * Structures
    *============================================================================*/

	typedef struct bsgfx_InstanceBuffer bsgfx_InstanceBuffer;
	struct bsgfx_InstanceBuffer {
		struct bsgfx_InstanceHeader header;
		char data[64];
	};



   /*==============================================================================
    * Interface
    *============================================================================*/

	BSGFXAPI bs_List* 
	bsgfx_subtypeInstances(
		int subtype);

	BSGFXAPI void 
	bsgfx_iniInstances();

	BSGFXAPI void
	bsgfx_instanceType(
		int type,
		int max_instance_count,
		int bind_set,
		int binding);

	BSGFXAPI bs_Range
	bsgfx_subtypeRange(
		int subtype);

	BSGFXAPI void bsgfx_deleteSubtype(int subtype);

	int bsgfx_instanceCount(int subtype);

	int bsgfx_subtypeCount(int instance_type_id);

	BSGFXAPI const int*
	bsgfx_subtypes();

	BSGFXAPI int
	bsgfx_subtype(
		int type,
		bs_Batch* batch,
		bs_U32 flags,
		bs_Range range);

	BSGFXAPI int
	bsgfx_instance(
		int subtype,
		const char* data,
		int data_size,
		bs_U32 flags,
		unsigned int bone_index,
		int id,
		int material);

	BSGFXAPI void
	bsgfx_tickInstances();

	BSGFXAPI bool
	bsgfx_subtypeHasFlag(
		int subtype,
		bs_U32 flag);

	BSGFXAPI void 
	bsgfx_renderSubtype(
		int subtype, 
		bs_Pipeline* pipeline);

	BSGFXAPI void 
	bsgfx_resetInstances();

	BSGFXAPI void
	bsgfx_resetSubtype(
		int subtype);

	BSGFXAPI void 
	bsgfx_instanceHiResMesh(
		bs_Mesh* mesh, 
		bs_vec3 position, 
		bs_vec4 rotation, 
		float scale, 
		int subtype_offset,
		bool origin_at_center);



   /*==============================================================================
    * Helpers
    *============================================================================*/

	static inline bs_vec4 bsgfx_convertColor(bs_RGBA color) {
		return bs_v4((float)color.r / 255.0, (float)color.g / 255.0, (float)color.b / 255.0, (float)color.a / 255.0);
	}

	static inline void bsgfx_instanceLineSubtype(bs_vec3 start, bs_vec3 end, bs_RGBA color, int subtype) {
		struct {
			bs_vec4 start, end, color;
		} data = {
			.start.xyz = start,
			.end.xyz = end,
			.color = bs_v4((float)color.r / 255.0, (float)color.g / 255.0, (float)color.b / 255.0, (float)color.a / 255.0)
		};

		bsgfx_instance(subtype, &data, sizeof(data), 0, 0, 0, 0);
	}

	typedef struct {
		bs_mat4 transform;
	} bsgfx_MeshInstance;

	typedef struct {
		bs_mat4 transform;
	} bsgfx_BoneInstance;

	static inline void bsgfx_meshInstance(int subtype, const bsgfx_MeshInstance* data, bs_U32 flags, int id, int material) {
		bsgfx_instance(subtype, data, sizeof(bsgfx_MeshInstance), flags, 0, id, material);
	}

	static inline void bsgfx_boneInstance(int subtype, const bsgfx_BoneInstance* data, bs_U32 flags, int id, int material) {
		bsgfx_instance(subtype, data, sizeof(bsgfx_BoneInstance), flags, 0, id, material);
	}

	static inline void bsgfx_lineScreenInstance(bs_vec3 start, bs_vec3 end, bs_RGBA color) {
		bsgfx_instanceLineSubtype(start, end, color, bsgfx_subtypes()[BSGFX_SUBTYPE_LINE]);
	}

	static inline void bsgfx_depthlessLineInstance(bs_vec3 start, bs_vec3 end, bs_RGBA color) {
		bsgfx_instanceLineSubtype(start, end, color, bsgfx_subtypes()[BSGFX_SUBTYPE_LINE_DEPTHLESS]);
	}

	static inline void bsgfx_transformedDepthlessLineInstance(bs_vec3 start, bs_vec3 end, bs_RGBA color, bs_mat4* transform) {
		bsgfx_instanceLineSubtype(bs_m4MulV3(*transform, start), bs_m4MulV3(*transform, end), color, bsgfx_subtypes()[BSGFX_SUBTYPE_LINE_DEPTHLESS]);
	}

	static inline void bsgfx_instanceLine(bs_vec3 start, bs_vec3 end, bs_RGBA color) {
		bsgfx_instanceLineSubtype(start, end, color, bsgfx_subtypes()[BSGFX_SUBTYPE_LINE]);
	}

	static inline void bsgfx_transformedLineInstance(bs_vec3 start, bs_vec3 end, bs_RGBA color, bs_mat4* transform) {
		bsgfx_instanceLineSubtype(bs_m4MulV3(*transform, start), bs_m4MulV3(*transform, end), color, bsgfx_subtypes()[BSGFX_SUBTYPE_LINE]);
	}

	static inline void bsgfx_instanceRay(const bs_Ray* ray, bs_RGBA color) {
		bsgfx_instanceLineSubtype(ray->origin, bs_v3Add(ray->origin, bs_v3MulV1(ray->direction, ray->length)), color, bsgfx_subtypes()[BSGFX_SUBTYPE_LINE]);
	}

	static inline void bsgfx_aabbInstance(const bs_Aabb* aabb, bs_RGBA color) {
		bsgfx_instanceLine(aabb->min, bs_v3(aabb->max.x, aabb->min.y, aabb->min.z), color);
		bsgfx_instanceLine(aabb->min, bs_v3(aabb->min.x, aabb->min.y, aabb->max.z), color);
		bsgfx_instanceLine(bs_v3(aabb->max.x, aabb->min.y, aabb->max.z), bs_v3(aabb->max.x, aabb->min.y, aabb->min.z), color);
		bsgfx_instanceLine(bs_v3(aabb->max.x, aabb->min.y, aabb->max.z), bs_v3(aabb->min.x, aabb->min.y, aabb->max.z), color);
		bsgfx_instanceLine(aabb->max, bs_v3(aabb->min.x, aabb->max.y, aabb->max.z), color);
		bsgfx_instanceLine(aabb->max, bs_v3(aabb->max.x, aabb->max.y, aabb->min.z), color);
		bsgfx_instanceLine(bs_v3(aabb->min.x, aabb->max.y, aabb->min.z), bs_v3(aabb->min.x, aabb->max.y, aabb->max.z), color);
		bsgfx_instanceLine(bs_v3(aabb->min.x, aabb->max.y, aabb->min.z), bs_v3(aabb->max.x, aabb->max.y, aabb->min.z), color);
		bsgfx_instanceLine(aabb->min, bs_v3(aabb->min.x, aabb->max.y, aabb->min.z), color);
		bsgfx_instanceLine(bs_v3(aabb->min.x, aabb->min.y, aabb->max.z), bs_v3(aabb->min.x, aabb->max.y, aabb->max.z), color);
		bsgfx_instanceLine(bs_v3(aabb->max.x, aabb->min.y, aabb->min.z), bs_v3(aabb->max.x, aabb->max.y, aabb->min.z), color);
		bsgfx_instanceLine(bs_v3(aabb->max.x, aabb->min.y, aabb->max.z), bs_v3(aabb->max.x, aabb->max.y, aabb->max.z), color);
	}

	static inline void bsgfx_obbInstance(const bs_Aabb* aabb, bs_RGBA color, bs_mat4* transform) {
		bsgfx_transformedDepthlessLineInstance(aabb->min, bs_v3(aabb->max.x, aabb->min.y, aabb->min.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(aabb->min, bs_v3(aabb->min.x, aabb->min.y, aabb->max.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(bs_v3(aabb->max.x, aabb->min.y, aabb->max.z), bs_v3(aabb->max.x, aabb->min.y, aabb->min.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(bs_v3(aabb->max.x, aabb->min.y, aabb->max.z), bs_v3(aabb->min.x, aabb->min.y, aabb->max.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(aabb->max, bs_v3(aabb->min.x, aabb->max.y, aabb->max.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(aabb->max, bs_v3(aabb->max.x, aabb->max.y, aabb->min.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(bs_v3(aabb->min.x, aabb->max.y, aabb->min.z), bs_v3(aabb->min.x, aabb->max.y, aabb->max.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(bs_v3(aabb->min.x, aabb->max.y, aabb->min.z), bs_v3(aabb->max.x, aabb->max.y, aabb->min.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(aabb->min, bs_v3(aabb->min.x, aabb->max.y, aabb->min.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(bs_v3(aabb->min.x, aabb->min.y, aabb->max.z), bs_v3(aabb->min.x, aabb->max.y, aabb->max.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(bs_v3(aabb->max.x, aabb->min.y, aabb->min.z), bs_v3(aabb->max.x, aabb->max.y, aabb->min.z), color, transform);
		bsgfx_transformedDepthlessLineInstance(bs_v3(aabb->max.x, aabb->min.y, aabb->max.z), bs_v3(aabb->max.x, aabb->max.y, aabb->max.z), color, transform);
	}

	static inline void bsgfx_instanceSphere(bs_vec3 position, float radius) {
		bs_mat4 transform = bs_scale(bs_translate(BS_MAT4_IDENTITY, position), bs_v3V1(radius));
		bsgfx_instance(bsgfx_subtypes()[BSGFX_SUBTYPE_SPHERE_MESH], &transform, sizeof(bs_mat4), 0, 0, 0, 0);
	}

	static inline void bsgfx_instanceCone(bs_mat4 transform, float radius, bs_U32 flags, int id, int material) {
		bsgfx_instance(bsgfx_subtypes()[BSGFX_SUBTYPE_CONE_MESH], &transform, sizeof(bs_mat4), flags, 0, id, material);
	}

	static inline void bsgfx_instancePoint(bs_vec3 position, bs_RGBA color, float size) {
		struct {
			bs_vec3 coord;
			float size;
			bs_vec4 color;
		} data = {
			.coord = position,
			.size = size,
			.color = bsgfx_convertColor(color),
		};

		bsgfx_instance(bsgfx_subtypes()[BSGFX_SUBTYPE_POINT], &data, sizeof(data), 0, 0, 0, 0);
	}

	struct bsgfx_QuadInstance {
		bs_mat4x3 transform;
		bs_vec2 coords;
		bs_vec2 offset;
	};

	static inline int bsgfx_instanceQuad(int subtype, bs_mat4x3 transform, bs_vec4 coords, bs_U32 flags, int id, int material) {
		struct bsgfx_QuadInstance tmp = {
			.transform = transform,
			.offset = coords.xy,
			.coords = coords.zw,
		};

		return bsgfx_instance(subtype, &tmp, sizeof(tmp), flags, 0, id, material);
	}

	static inline void bsgfx_atlasInstance(int subtype, bs_mat4x3 transform, int texture, bs_U32 flags, int id, int material) {
		bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
		bs_vec4 coords = bs_atlasCoordinates(atlas, texture, 0);

		struct bsgfx_QuadInstance tmp = {
			.transform = transform,
			.offset = coords.xy,
			.coords = coords.zw,
		};

		bsgfx_instance(subtype, &tmp, sizeof(tmp), flags, 0, id, material);
	}

	static inline void bsgfx_atlasInstanceFlipped(int subtype, bs_mat4x3 transform, int texture, bs_U32 flags, int id, int material) {
		bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
		bs_vec4 coords = bs_atlasCoordinates(atlas, texture, 0);
		coords = bs_mirrorUV(coords);

		struct bsgfx_QuadInstance tmp = {
			.transform = transform,
			.offset = coords.xy,
			.coords = coords.zw,
		};

		bsgfx_instance(subtype, &tmp, sizeof(tmp), flags, 0, id, material);
	}

	static inline void bsgfx_transformedDepthlessCircle(bs_mat4 transform, int segments, float radius, bs_RGBA color) {
		float prev_x = 0.0f, prev_z = 0.0f;
		for (int i = 0; i <= segments; i++) {
			float ratio = (float)i / segments;
			float r = ratio * BS_2PI;
			float x = cos(r) * radius;
			float z = sin(r) * radius;

			if (i > 0)
				bsgfx_transformedDepthlessLineInstance(
					bs_v3(prev_x, 0.0, prev_z),
					bs_v3(x, 0.0, z),
					color,
					&transform
				);

			prev_x = x;
			prev_z = z;
		}
	}

	static inline bs_mat4x3 bsgfx_matrix(bs_vec3 position, bs_vec3 scale) {
		return (bs_mat4x3) {
			scale.x, 0.0, 0.0,
			0.0, scale.y, 0.0,
			0.0, 0.0, scale.z,
			position.x, position.y, position.z,
		};
	}



  /*==============================================================================
   * Text
   *============================================================================*/

	enum {
		BSGFX_FONT_FORCE_CREATE = 1 << 0,
		BSGFX_FONT_NO_CAPS = 1 << 1,
	};

#define BSGFX_ALPHABET_DEFAULT " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"


	BSGFXAPI void
		bsgfx_renderFontSubtypes();

	typedef struct {
		bs_vec4 position;
		float scale;
		float max_length;
		bs_U32 flags;
		int select_start, select_end;
		int material_id;
		bs_RGBA colors[8];
	} bsgfx_Text;

	static inline bs_vec2 bsgfx_textInstance(int subtype, bs_Font* font, bsgfx_Text* params, const char* text, int text_length) {
		if (!text)
			text = "(null)";

		bs_RGBA color = BS_WHITE;

		bs_vec2 offset = bs_v2V1(0);
		bs_mat4 transform = bs_transform(params->position.xyz, BS_QUAT_IDENTITY, bs_v3V2(bs_v2MulV1(bs_v2(font->spacing, font->atlas->mapped[0].h), params->scale), 0.0));
		bs_U32 flags;
		float layout_scale = (params->scale / (float)font->units_per_em);

		for (int i = 0; i < text_length; i++) {
			char c = text[i];
			int index = font->table[c];
			if (index >= font->atlas->count)
				index = 0;

			flags = params->flags;
			if ((params->select_end || params->select_start) && (
				(i >= params->select_start && i < params->select_end) ||
				(i > params->select_end && i <= params->select_start))) {
				flags |= BSGFX_ID_FONT_IS_SELECTED;
			}

			float spacing = font->glyphs[index].advance_width * layout_scale;
			if (c == ' ') {
				float new_offset = offset.x + spacing * layout_scale;
				if (params->max_length > 0.0 && new_offset > params->max_length)
					break;

				transform.v[3].x = params->position.x + offset.x;
				transform.v[3].y = params->position.y + offset.y;
				transform.v[0].x = spacing * layout_scale;
				transform.v[1].y = font->height * layout_scale;
				//bsgfx_instanceQuad(subtype, bs_m4x3(transform), bs_v4(0, 0, 0, 0), flags, 0, 0);

				offset.x = new_offset;
				continue;
			}
			else if (c == '\n') {
				offset.x = 0.0;
				offset.y -= font->height * layout_scale;
				continue;
			}

			bs_vec4 coords = bs_atlasCoordinates(font->atlas, index, 0);
			bs_vec2 size = bs_atlasSize(font->atlas, index);

			float new_offset = offset.x + size.x * layout_scale;
			if (params->max_length > 0.0 && new_offset > params->max_length)
				break;

			transform.v[3].x = params->position.x + offset.x;
			transform.v[3].y = params->position.y + offset.y + ((float)font->glyphs[index].y_offset) * layout_scale;
			transform.v[0].x = (size.x + font->glyphs[index].left_side_bearing) * layout_scale;
			transform.v[1].y = size.y * layout_scale;

			bsgfx_instanceQuad(subtype, bs_m4x3(transform), coords, flags, 0, params->material_id);
			offset.x += spacing;

			if (i <= (text_length - 1)) {
				char next = text[i + 1];
				int next_index = font->table[next];

				for (int j = font->glyphs[index].kerning_pair_offset; j < (font->glyphs[index].kerning_pair_offset + font->glyphs[index].kerning_pair_count); j++) {
					if (next_index == font->pairs[j].right) {
						offset.x += font->pairs[j].value;
						break;
					}
				}
			}

		}

		return offset;
	}

	static inline bs_vec2 bsgfx_textInstanceV(int subtype, const bs_Font* font, const bsgfx_Text* params, const char* format, va_list args) {
		static bs_String* formatted;
		formatted = bs_stringV(formatted, format, args);
		return bsgfx_textInstance(subtype, font, params, formatted->value, formatted->len);
	}

	static inline bs_vec2 bsgfx_textInstanceF(int subtype, const bs_Font* font, const bsgfx_Text* params, const char* format, ...) {
		va_list args;
		va_start(args, format);
		bs_vec2 dim = bsgfx_textInstanceV(subtype, font, params, format, args);
		va_end(args);
		return dim;
	}

#endif