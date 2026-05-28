 
 /**
  bs_json.h
  JSON, JPath
  */

#ifndef BS_JSON_H
#define BS_JSON_H

#include <bs_types.h>
#include <bs_mem.h>



  /*==============================================================================
   * Macros
   *============================================================================*/

	typedef bs_U32 bs_SaveJsonBits;

	#define BS_JSON_PRETTY							(1 << 0)
	#define BS_JSON_ESCAPE_UNICODE					(1 << 1)
	#define BS_JSON_ESCAPE_SLASHES					(1 << 2)
	#define BS_JSON_ALLOW_INF_AND_NAN				(1 << 3)
	#define BS_JSON_INF_AND_NAN_AS_NULL				(1 << 4)
	#define BS_JSON_ALLOW_INVALID_UNICODE			(1 << 5)
	#define BS_JSON_PRETTY_TWO_SPACES				(1 << 6)
	#define BS_JSON_NEWLINE_AT_END					(1 << 7)



  /*==============================================================================
   * JSON
   *============================================================================*/
	BSAPI bs_JsonEnumeration bs_beginEnumeration(bs_Json* json);
	BSAPI void bs_enumerateJson(bs_Json* json, bs_JsonEnumeration* e);

#define bs_foreachJson(json, e) \
	for (bs_JsonEnumeration e = bs_beginEnumeration(json); e.key; bs_enumerateJson(json, &e))


   /**
    Create a root from an object
	@param json - Document to create object in, or NULL to make a new document
	@param object
	*/
	BSAPI bs_Json
	bs_jsonRoot(
		bs_Json* json,
		bs_JsonObject object);

	BSAPI void bs_ensureJsonMutable(bs_Json* root);
	BSAPI bs_Json bs_jsonCopy(const bs_Json* root);

   /**
    Serialize a json document
	TODO: does this need to be freed?
	@param json
	@param flags
	@returns JSON string
    */
	BSAPI char*
	bs_saveJson(
		bs_Json* json,
		bs_SaveJsonBits flags);

   /**
    Create an empty {} JSON document
	@returns JSON document
	*/
	BSAPI bs_Json
	bs_emptyJson();

	BSAPI bs_Json
	bs_emptyJsonArray();

   /**
    Create a JSON document from a raw string
	@param raw
	@param len - Length of the JSON string
	@returns JSON document
    */
	BSAPI bs_Json
	bs_json(
		char* raw,
		int len);

   /**
	Load a JSON document from a path to a JSON file
	@param path
	@returns JSON document
	@throws BSX_INVALID_JSON
    */
	BSAPI bs_Json
	bs_loadJson(
		const char* path);

   /**
	Load a JSON document from a format path to a JSON file
	@param format
	@param ...
	@throws BSX_INVALID_JSON 
    */
	BSAPI bs_Json
	bs_loadJsonF(
		char* format,
		...);

   /**
    Deallocate a JSON document and all of its resources
	@param json
    */
	BSAPI void
	bs_destroyJson(
		bs_Json* json);

   /**
    Parses a single JSON value
	@param raw - String containing a single JSON value
	@returns Parsed json value
    */
	BSAPI bs_JsonValue
	bs_parseJsonValue(
		char* raw);



  /*==============================================================================
   * JPath
   *============================================================================*/

   /**
   
    $					The root object or array
    .property			Selects the specified property in a parent object
    [n]					Selects the n-th element from an array
    [n1, n2]			Selects array elements with the specified indexes
    [start:end]			Selects array elements from the start index and up to, but not including, end index.
    [start:]			Selects array elements from the start index
    [:n]				Selects the first n elements of the array
    [-n:]				Selects the last n elements of the array


	For example:

		JSON:
		{
			"test": {
				"abc": [
					1,
					2,
					3
				]
			}
		}

		JPath:
		$.test.abc = [1, 2, 3]
		$.test.abc[0] = 1
		$.test.abc[1] = 2
		$.test.abc[1, 2] = [2, 3]

    */


   /**
    Find a json value from a JPath
    @param root
	@param expect - Expected datatype, BS_JSON_UNDEFINED to ignore all errors, BS_JSON_DONT_CARE to ignore type errors
	@param path - JPath
	@returns Value found at the specified path
    */
	BSAPI bs_JsonValue
	bs_fetchJson(
		bs_Json* root,
		bs_JsonType expect,
		char* path);

   /**
    Same as bs_fetchJson(...), but with a format as path
    */
	BSAPI bs_JsonValue
	bs_fetchJsonF(
		bs_Json* root,
		bs_JsonType expect,
		const char* format, 
		...);

	BSAPI void
	bs_deleteJson(
		bs_Json* root, 
		char* path);

	BSAPI void
	bs_deleteJsonF(
		bs_Json* root,
		const char* format,
		...);

   /**
    Create or update a JSON value at the specified JPath
	@param root
	@param value - The value to replace/place at the path
	@param path
	@returns todo 
    */
	BSAPI bool
	bs_ensureJson(
		bs_Json* root,
		bs_JsonValue value,
		char* path);

   /**
	Same as bs_ensureJson(...), but with a format as path
	*/
	BSAPI bool
	bs_ensureJsonF(
		bs_Json* root,
		bs_JsonValue value,
		const char* path,
		...);

	BSAPI bs_JsonValue bs_jsonValueFromObject(bs_JsonObject x);
	BSAPI bs_JsonValue bs_jsonValueFromRoot(bs_Json x);
	BSAPI bs_JsonValue bs_jsonValueFromBool(bool x);
	BSAPI bs_JsonValue bs_jsonValueFromInteger(int x);
	BSAPI bs_JsonValue bs_jsonValueFromFloat(double x);
	BSAPI bs_JsonValue bs_jsonValueFromString(char* x);
	BSAPI bs_JsonValue bs_jsonValueFromStringPointer(char* x);
	BSAPI bs_JsonValue bs_jsonValueFromDateTime(bs_DateTime x);
	BSAPI bs_JsonValue bs_jsonObject(bs_Json* json);
	BSAPI bs_JsonValue bs_jsonArray(bs_JsonType type, char* data, int count);
	BSAPI bs_JsonValue bs_jsonVec2(bs_vec2* vector);
	BSAPI bs_JsonValue bs_jsonVec3(bs_vec3* vector);
	BSAPI bs_JsonValue bs_jsonVec4(bs_vec4* vector);
	BSAPI bs_JsonValue bs_jsonRGBA(bs_RGBA color);

   /**
    Generic macro for creating a json value
	@param x - Any valid value
	@returns Created json value
	*/
	#define bs_jsonValue(x) _Generic((0, x), \
		int: bs_jsonValueFromInteger, \
		long: bs_jsonValueFromInteger, \
		long long: bs_jsonValueFromInteger, \
		unsigned int: bs_jsonValueFromInteger, \
		unsigned long: bs_jsonValueFromInteger, \
		unsigned long long: bs_jsonValueFromInteger, \
		short: bs_jsonValueFromInteger, \
		unsigned short: bs_jsonValueFromInteger, \
		char: bs_jsonValueFromInteger, \
		unsigned char: bs_jsonValueFromInteger, \
		bool: bs_jsonValueFromBool, \
		float: bs_jsonValueFromFloat, \
		double: bs_jsonValueFromFloat, \
		char*: bs_jsonValueFromString, \
		const char*: bs_jsonValueFromString, \
		bs_Json: bs_jsonValueFromRoot, \
		bs_DateTime: bs_jsonValueFromDateTime, \
		bs_RGBA: bs_jsonRGBA, \
		bs_vec2*: bs_jsonVec2, \
		bs_vec3*: bs_jsonVec3, \
		bs_vec4*: bs_jsonVec4 \
	)(x)


	#define BS_JSONIFY_FIELD(field, value) bs_ensureJson(&_tmp, bs_jsonValue(value), field);

	#define BS_JSONIFY(json, ...) \
		({ \
			bs_JsonValue _obj = bs_jsonObject(); \
			bs_Json _tmp = bs_jsonRoot(json, _obj.as_object); \
			__VA_FOR_2__(BS_JSONIFY_FIELD, __VA_ARGS__); \
			_obj; \
		})

#endif