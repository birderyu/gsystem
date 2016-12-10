/// 二进制字节流

#ifndef _CORE_BYTES_H_
#define _CORE_BYTES_H_

#include "CsObject.h"

#define CS_DEFAULT_BUF_SIZE 4096

class CsBytes_Ex;

class CS_API CsBytes 
	: public CsObject
{
public:
	CsBytes(cs_size_t nBufSize = CS_DEFAULT_BUF_SIZE);
	CsBytes(const CsBytes &tBytes);
	~CsBytes();

	cs_void Clear();
	cs_bool IsEmpty() const;
	cs_byte *GetBuffer() const;
	cs_size_t Length() const;
	cs_bool ReadFrom(const cs_byte *pBuf, cs_size_t len);
	cs_bool WriteTo(cs_size_t len, cs_byte *&pBuf);
	cs_bool WriteAllTo(cs_byte *&pBuf);

	/// 写入二进制字节流
	CsBytes &operator<<(cs_bool);
	CsBytes &operator<<(cs_char);
	CsBytes &operator<<(cs_schar);
	CsBytes &operator<<(cs_uchar);
	CsBytes &operator<<(cs_wchar);
	CsBytes &operator<<(cs_short);
	CsBytes &operator<<(cs_ushort);
	CsBytes &operator<<(cs_int);
	CsBytes &operator<<(cs_uint);
	CsBytes &operator<<(cs_long);
	CsBytes &operator<<(cs_ulong);
	CsBytes &operator<<(cs_longlong);
	CsBytes &operator<<(cs_ulonglong);
	CsBytes &operator<<(cs_float);
	CsBytes &operator<<(cs_double);
	CsBytes &operator<<(cs_decimal);
	CsBytes &operator<<(const CsString &);
	CsBytes &operator<<(const CsBytes &);
	//CsBytes &operator<<(const CsVariant &);
	//CsBytes &operator<<(const CsObject *);

	/// 从二进制字节流中写出
	const CsBytes &operator>>(cs_bool &) const;
	const CsBytes &operator>>(cs_char &) const;
	const CsBytes &operator>>(cs_schar &) const;
	const CsBytes &operator>>(cs_uchar &) const;
	const CsBytes &operator>>(cs_wchar &) const;
	const CsBytes &operator>>(cs_short &) const;
	const CsBytes &operator>>(cs_ushort &) const;
	const CsBytes &operator>>(cs_int &) const;
	const CsBytes &operator>>(cs_uint &) const;
	const CsBytes &operator>>(cs_long &) const;
	const CsBytes &operator>>(cs_ulong &) const;
	const CsBytes &operator>>(cs_longlong &) const;
	const CsBytes &operator>>(cs_ulonglong &) const;
	const CsBytes &operator>>(cs_float &) const;
	const CsBytes &operator>>(cs_double &) const;
	const CsBytes &operator>>(cs_decimal &) const;
	const CsBytes &operator>>(CsString &) const;
	const CsBytes &operator>>(CsBytes &) const;

private:
	CsBytes_Ex *m_pBytes_Ex;
};

#endif // _CORE_BYTES_H_