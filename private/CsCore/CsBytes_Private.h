#ifndef _CORE_BYTES_PRIVATE_H_
#define _CORE_BYTES_PRIVATE_H_

#include "CsObject_Private.h"

class CsBytes;
class CsString;

class CsBytes_Private :public CsObject_Private
{
private:
	/// 内存池
	static CsMemoryPool m_tMemoryPool;

public:
	CsBytes_Private(CsBytes *pPublic, const cs_size_t nCapacity);
	CsBytes_Private(CsBytes *pPublic, const CsBytes_Private &tBytes);
	~CsBytes_Private();

	cs_bool IsEmpty() const;
	cs_byte *GetBuffer() const;

	/// 写入二进制字节流
	template<typename T>
	cs_bool operator<<(const T &value);

	/// 从二进制字节流中写出
	template<typename T>
	cs_bool operator>>(T &value) const;

private:
	cs_bool Alloc();
	cs_void Free();
	cs_byte *m_pBuffer;
	cs_size_t m_nCapacity;
	cs_size_t m_nLength;
};

template<typename T>
cs_bool CsBytes_Private::operator << (const T &value)
{
	return false;
}

template<typename T>
cs_bool CsBytes_Private::operator >> (T &value) const
{
	return false;
}

#endif // _CORE_BYTES_PRIVATE_H_