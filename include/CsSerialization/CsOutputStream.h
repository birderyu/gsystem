// Êä³öÁ÷
#ifndef _CORE_OUTPUT_STREAM_H_
#define _CORE_OUTPUT_STREAM_H_

#include "CsStream.h"

class CS_API CsOutputStream
	: virtual public CsStream
{
public:
	virtual ~CsOutputStream() = 0;
	cs_bool IsOutput() const;

	virtual CsOutputStream &operator>>(cs_bool &) = 0;
	virtual CsOutputStream &operator>>(cs_char &) = 0;
	virtual CsOutputStream &operator>>(cs_schar &) = 0;
	virtual CsOutputStream &operator>>(cs_uchar &) = 0;
	virtual CsOutputStream &operator>>(cs_wchar &) = 0;
	virtual CsOutputStream &operator>>(cs_short &) = 0;
	virtual CsOutputStream &operator>>(cs_ushort &) = 0;
	virtual CsOutputStream &operator>>(cs_int &) = 0;
	virtual CsOutputStream &operator>>(cs_uint &) = 0;
	virtual CsOutputStream &operator>>(cs_long &) = 0;
	virtual CsOutputStream &operator>>(cs_ulong &) = 0;
	virtual CsOutputStream &operator>>(cs_longlong &) = 0;
	virtual CsOutputStream &operator>>(cs_ulonglong &) = 0;
	virtual CsOutputStream &operator>>(cs_float &) = 0;
	virtual CsOutputStream &operator>>(cs_double &) = 0;
	virtual CsOutputStream &operator>>(cs_decimal &) = 0;
};

#endif // _CORE_OUTPUT_STREAM_H_