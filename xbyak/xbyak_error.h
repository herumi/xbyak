#ifndef XBYAK_XBYAK_ERROR_H_
#define XBYAK_XBYAK_ERROR_H_

#include <assert.h>
#include <stdlib.h>
#include <exception>
namespace Xbyak {

enum {
	ERR_NONE = 0,
	ERR_BAD_ADDRESSING,
	ERR_CODE_IS_TOO_BIG,
	ERR_BAD_SCALE,
	ERR_ESP_CANT_BE_INDEX,
	ERR_BAD_COMBINATION,
	ERR_BAD_SIZE_OF_REGISTER,
	ERR_IMM_IS_TOO_BIG,
	ERR_BAD_ALIGN,
	ERR_LABEL_IS_REDEFINED,
	ERR_LABEL_IS_TOO_FAR,
	ERR_LABEL_IS_NOT_FOUND,
	ERR_CODE_ISNOT_COPYABLE,
	ERR_BAD_PARAMETER,
	ERR_CANT_PROTECT,
	ERR_CANT_USE_64BIT_DISP,
	ERR_OFFSET_IS_TOO_BIG,
	ERR_MEM_SIZE_IS_NOT_SPECIFIED,
	ERR_BAD_MEM_SIZE,
	ERR_BAD_ST_COMBINATION,
	ERR_OVER_LOCAL_LABEL, // not used
	ERR_UNDER_LOCAL_LABEL,
	ERR_CANT_ALLOC,
	ERR_ONLY_T_NEAR_IS_SUPPORTED_IN_AUTO_GROW,
	ERR_BAD_PROTECT_MODE,
	ERR_BAD_PNUM,
	ERR_BAD_TNUM,
	ERR_BAD_VSIB_ADDRESSING,
	ERR_CANT_CONVERT,
	ERR_LABEL_ISNOT_SET_BY_L,
	ERR_LABEL_IS_ALREADY_SET_BY_L,
	ERR_BAD_LABEL_STR,
	ERR_MUNMAP,
	ERR_OPMASK_IS_ALREADY_SET,
	ERR_ROUNDING_IS_ALREADY_SET,
	ERR_K0_IS_INVALID,
	ERR_EVEX_IS_INVALID,
	ERR_SAE_IS_INVALID,
	ERR_ER_IS_INVALID,
	ERR_INVALID_BROADCAST,
	ERR_INVALID_OPMASK_WITH_MEMORY,
	ERR_INVALID_ZERO,
	ERR_INVALID_RIP_IN_AUTO_GROW,
	ERR_INVALID_MIB_ADDRESS,
	ERR_X2APIC_IS_NOT_SUPPORTED,
	ERR_NOT_SUPPORTED,
	ERR_INTERNAL // Put it at last.
};

#ifndef XBYAK_NOEXCEPT
    #define XBYAK_SET_STATUS(err) throw Error(err)
    #define XBYAK_GET_STATUS ERR_NONE
#else
    #if (__cplusplus >= 201103)
        #define THREAD_LOCAL _Thread_local
    #else
        #if defined(WIN32)
        #define THREAD_LOCAL __declspec(thread)
        #else
        #define THREAD_LOCAL __thread
        #endif
    #endif
class Status {
private:
    int status_;
    Status() : status_(ERR_NONE) {}
#if (__cplusplus < 201103)
    Status& operator=(const Status& other);
    Status(const Status& other);
#else
public:
    Status& operator=(const Status& other) = delete;
    Status(const Status& other) = delete;
#endif
    static Status& instance() {
        THREAD_LOCAL static Status instance;
        return instance;
    }
    void setStatus(int status) {
        status_ = status;
    }
    bool getStatus() const { return status_; }

};

    #define XBYAK_SET_STATUS(err) Xbyak::Status::instance().setStatus(err)
    #define XBYAK_GET_STATUS Xbyak::Status::instance().getStatus()
#endif

class Error : public std::exception {
	int err_;
public:
	explicit Error(int err) : err_(err)
	{
		if (err_ < 0 || err_ > ERR_INTERNAL) {
			err_ = ERR_INTERNAL;
		}
	}
	operator int() const { return err_; }
	const char *what() const throw()
	{
		static const char *errTbl[] = {
			"none",
			"bad addressing",
			"code is too big",
			"bad scale",
			"esp can't be index",
			"bad combination",
			"bad size of register",
			"imm is too big",
			"bad align",
			"label is redefined",
			"label is too far",
			"label is not found",
			"code is not copyable",
			"bad parameter",
			"can't protect",
			"can't use 64bit disp(use (void*))",
			"offset is too big",
			"MEM size is not specified",
			"bad mem size",
			"bad st combination",
			"over local label",
			"under local label",
			"can't alloc",
			"T_SHORT is not supported in AutoGrow",
			"bad protect mode",
			"bad pNum",
			"bad tNum",
			"bad vsib addressing",
			"can't convert",
			"label is not set by L()",
			"label is already set by L()",
			"bad label string",
			"err munmap",
			"opmask is already set",
			"rounding is already set",
			"k0 is invalid",
			"evex is invalid",
			"sae(suppress all exceptions) is invalid",
			"er(embedded rounding) is invalid",
			"invalid broadcast",
			"invalid opmask with memory",
			"invalid zero",
			"invalid rip in AutoGrow",
			"invalid mib address",
			"x2APIC is not supported",
			"not supported",
			"internal error"
		};
		assert(err_ <= ERR_INTERNAL);
		assert(ERR_INTERNAL + 1 == sizeof(errTbl) / sizeof(*errTbl));
		return errTbl[err_];
	}
};

}

#endif
