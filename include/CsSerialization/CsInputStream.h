//  ‰»Î¡˜
#ifndef _CORE_INPUT_STREAM_H_
#define _CORE_INPUT_STREAM_H_

#include "CsStream.h"

class CS_API CsInputStream
	: virtual public CsStream
{
public:
	virtual ~CsInputStream() = 0;
	cs_bool IsInput() const;

	virtual CsInputStream &operator<<(cs_bool) = 0;
	virtual CsInputStream &operator<<(cs_char) = 0;
	virtual CsInputStream &operator<<(cs_schar) = 0;
	virtual CsInputStream &operator<<(cs_uchar) = 0;
	virtual CsInputStream &operator<<(cs_wchar) = 0;
	virtual CsInputStream &operator<<(cs_short) = 0;
	virtual CsInputStream &operator<<(cs_ushort) = 0;
	virtual CsInputStream &operator<<(cs_int) = 0;
	virtual CsInputStream &operator<<(cs_uint) = 0;
	virtual CsInputStream &operator<<(cs_long) = 0;
	virtual CsInputStream &operator<<(cs_ulong) = 0;
	virtual CsInputStream &operator<<(cs_longlong) = 0;
	virtual CsInputStream &operator<<(cs_ulonglong) = 0;
	virtual CsInputStream &operator<<(cs_float) = 0;
	virtual CsInputStream &operator<<(cs_double) = 0;
	virtual CsInputStream &operator<<(cs_decimal) = 0;
};

#endif // _CORE_INPUT_STREAM_H_