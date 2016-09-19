/// 二进制字节流

#ifndef _CORE_BYTES_H_
#define _CORE_BYTES_H_

#include "CsObject.h"
#define CS_DEFAULT_BUF_SIZE 4096

class CS_CORE_EXPORT CsBytes :public CsObject
{
public:
	CsBytes(const cs_size_t nBufSize = CS_DEFAULT_BUF_SIZE);
	CsBytes(const CsBytes &tBytes);

	cs_bool IsEmpty() const;
	cs_bool CutTo(const cs_size_t nStart, const cs_size_t nLength, CsBytes &tBytes);
	cs_byte *ToCArray() const;
	cs_size_t Length() const;

	/// 写入二进制字节流
	CsBytes &operator<<(const cs_int8 i8);
	CsBytes &operator<<(const cs_uint8 ui8);
	CsBytes &operator<<(const cs_int16 i16);
	CsBytes &operator<<(const cs_uint16 ui16);
	CsBytes &operator<<(const cs_int32 i32);
	CsBytes &operator<<(const cs_uint32 ui32);
	CsBytes &operator<<(const cs_int64 i64);
	CsBytes &operator<<(const cs_uint64 ui64);
	CsBytes &operator<<(const cs_float f);
	CsBytes &operator<<(const cs_double d);
	CsBytes &operator<<(const CsString &s);

	/// 从二进制字节流中写出
	const CsBytes &operator>>(cs_int8 &value) const;
	const CsBytes &operator>>(cs_uint8 &value) const;
	const CsBytes &operator>>(cs_int16 &value) const;
	const CsBytes &operator>>(cs_uint16 &value) const;
	const CsBytes &operator>>(cs_int32 &value) const;
	const CsBytes &operator>>(cs_uint32 &value) const;
	const CsBytes &operator>>(cs_int64 &value) const;
	const CsBytes &operator>>(cs_uint64 &value) const;
	const CsBytes &operator>>(cs_float &value) const;
	const CsBytes &operator>>(cs_double &value) const;
	const CsBytes &operator>>(CsString &value) const;
};

#endif // _CORE_BYTES_H_