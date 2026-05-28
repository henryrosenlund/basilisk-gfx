
  /**
   bs_log.h
   Logging, error handling
   */

#ifndef BS_LOG_H
#define BS_LOG_H

#include <bs_types.h>
#include <bs_mem.h>

	#define BS_ALL_EXCEPTIONS 0xFFFFFFFFFFFFFFFF

   /** Variadic logs */

#define BS_ERROR_HEADER BS_PRINT_COLOR("[ERR] ", BS_PRINT_RED)
#define BS_WARN_HEADER BS_PRINT_COLOR("[WRN] ", BS_PRINT_YELLOW)
#define BS_INFO_HEADER BS_PRINT_COLOR("[INF] ", BS_PRINT_CYAN)

#ifdef _DEBUG
#define bs_assert(cond) \
    if (!(cond)) bs_throwBasiliskF(BSX_ASSERTION, "%s", #cond)
#else
#define bs_assert(cond)
#endif

	BSAPI char* bs_logSectionV(const char* format, va_list args);
	BSAPI char* bs_logSectionF(const char* format, ...);
	BSAPI char* bs_logEndOfSection();

   /**
    @param format
	@param args
    */
	BSAPI char* 
	bs_logWithTimestampV(
		const char* type, int type_len, const char* format, va_list args);

	BSAPI char*
	bs_logV(
		const char* format, va_list args);

   /**
    Formats a string and logs it as a warning
    @param format
	@param args
    */
	BSAPI char*
	bs_warnV(
		const char* format, 
		va_list args);

   /**
    Formats a string and logs it as an error, then immediately exits the application
	@param format
	@param args
	*/
	BSAPI void
	bs_throwV(
		const char* format, 
		va_list args);

   /**
	@param format
	@param ...
	*/
	BSAPI char*
	bs_infoF(
		const char* format, 
		...);

	BSAPI char* 
	bs_infoF(
		const char* format, 
		...);

   /**
    Formats a string and logs it as a warning
    @param format
    @param ...
    */
	BSAPI void
	bs_warnF(
		const char* format, 
		...);

   /**
    Formats a string and logs it as an error, then immediately exits the application
    @param format
    @param ...
    */
	BSAPI void
	bs_throwF(
		const char* format, 
		...);

	BSAPI void
	bs_throwBasilisk(
		bs_U64 code);

	BSAPI bs_U64
	bs_except(
		bs_U64 exceptions);

	BSAPI bool bs_caught();

	BSAPI const char*
	bs_exceptionName(
		bs_U64 code);

	BSAPI void
	bs_logBasilisk(
		bs_U64 code);

	BSAPI void
	bsi_throwBasiliskF(
		bs_U64 code,
		const char* format, 
		...);
	
#define bs_throwBasiliskF(code, format, ...) \
    bsi_throwBasiliskF(code, (format "\n%s:%d:%s(): "), __VA_ARGS__ __VA_OPT__(,) __FILE__, __LINE__, __func__)

	BSAPI void
	bs_throwErrno(
		const char* message);

	BSAPI void
	bs_throwVulkan(
		int result);
	bs_Result bs_convertVulkanResult(int result);

	BSAPI void
	bs_throwNotImplemented();

	BSAPI void
	bs_throwIfBufferTooSmall(
		bs_Buffer* buffer, 
		bs_U32 num_bytes);

	BSAPI void
	bs_throwIfNotMapped(
		bs_Buffer* buffer);

	BSAPI void
	bs_throwIfStringConversionFail(
		char* orig, 
		char* output);

	// windows

#ifdef _WIN32
	BSAPI bool
	bs_throwWin32Error(
		bs_U64 code,
		char* path);

	BSAPI bool
	bs_throwLastWin32Error(
		char* path);

	BSAPI void
	bs_throwHResult(
		long code,
		char* str);
#endif

	BSAPI void
	bs_logObjectDiff();

	BSAPI void
	bs_logUnchangedObjects();

	BSAPI void
	bs_logBindings();

	BSAPI void
	bs_infoF4(
		bs_mat4* m);

	#define BSX(x) ((uint64_t)1 << (x))

	#define BSX_UNKNOWN                         BSX(0)
	#define BSX_GENERAL                         BSX(1)
	#define BSXI_INTERNAL                       BSX(2)
	#define BSX_NO_GPU                          BSX(3)
	#define BSX_TIMEOUT                         BSX(4)
	#define BSX_NOT_IMPLEMENTED                 BSX(5)
	#define BSX_FAILED_TO_CONVERT               BSX(6)
	#define BSX_CORRUPTED						BSX(7)
	#define BSX_INVALID_TYPE                    BSX(8)
	#define BSX_UNKNOWN_TYPE_SIZE               BSX(9)
	#define BSX_FAILED_TO_QUERY                 BSX(10)
	#define BSX_FAILED_TO_CREATE                BSX(11)
	#define BSX_NOT_FOUND                       BSX(12)
	#define BSX_INVALID_PARAM                   BSX(13)
	#define BSX_INVALID_FORMAT                  BSX(14)
	#define BSX_ENSURE_RETURN                   BSX(15)
	#define BSX_DEVICE_LOST                     BSX(16)
	#define BSX_FAILED_TO_ACQUIRE               BSX(17)
	#define BSX_DUPLICATE						BSX(18)
	#define BSX_UNMAPPED_BUFFER                 BSX(19)
	#define BSX_INVALID_VERTEX_ATTRIBUTE        BSX(20)
	#define BSX_UNKNOWN_LAYOUT_TRANSITION       BSX(21)
	#define BSX_NO_DATA							BSX(22)
	#define BSX_NO_SHADER_STAGES                BSX(23)
	#define BSX_TOO_MANY_OPEN_FILES             BSX(24)
	#define BSX_PERMISSION_DENIED               BSX(25)
	#define BSX_BAD_PATH_NAME                   BSX(26)
	#define BSX_INVALID_NAME                    BSX(27)
	#define BSX_ALREADY_EXISTS                  BSX(28)
	#define BSX_INVALID_FILE_TYPE               BSX(29)
	#define BSX_INVALID_FILE_EXTENSION          BSX(30)
	#define BSX_FAILED_TO_WRITE                 BSX(31)
	#define BSX_INVALID_HANDLE                  BSX(32)
	#define BSX_FAILED_TO_ALLOCATE              BSX(33)
	#define BSX_OUT_OF_BOUNDS                   BSX(34)
	#define BSX_EXPECTED_UNSIGNED               BSX(35)
	#define BSX_UNINITIALIZED                   BSX(36)
	#define BSX_MISMATCH						BSX(37)
	#define BSX_VALIDATION						BSX(38)
	#define BSX_INTEGER_OVERFLOW                BSX(39)
	#define BSX_OUT_OF_ORDER                    BSX(40)
	#define BSX_IMMUTABLE						BSX(41)
	#define BSX_EXPECTED_END					BSX(42)
	#define BSX_CANT_CONNECT                    BSX(43)
	#define BSX_INVALID_URL                     BSX(44)
	#define BSX_INVALID_CONNECTION              BSX(45)
	#define BSXI_STEAM							BSX(46)
	#define BSX_NOT_A_NUMBER					BSX(47)
	#define BSX_FAILED_TO_INVOKE				BSX(48)
	#define BSXI_LOG_CAUGHT						BSX(49)
	#define BSX_ASSERTION						BSX(50)
	#define BSX_NOT_SUPPORTED					BSX(51)
	#define BSX_INVALID_STATE					BSX(52)

	#define BS_ASSERT_TYPE(obj, t1) do {									\
			int t2 = _bs_instance->objects[obj->head.id].object.type; \
            if (t1 != t2)	\
                bs_throwBasiliskF(BSX_ASSERTION, "%s != %s", \
					_bs_instance->object_types[t1].name, \
					_bs_instance->object_types[t2].name \
				); \
        } while (0)

#endif