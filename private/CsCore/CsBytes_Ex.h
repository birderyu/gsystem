#ifndef _CORE_BYTES_PRIVATE_H_
#define _CORE_BYTES_PRIVATE_H_

#include "CsEndian.h"
#include "CsBlock.h"
#include <string>

class CsString;

class CsBytes_Ex
{
public:
	CsBytes_Ex(cs_size_t nCapacity);
	CsBytes_Ex(const CsBytes_Ex &tBytes);
	~CsBytes_Ex();

	cs_void Clear();
	cs_bool IsEmpty() const;
	cs_byte *GetHead() const;
	cs_size_t Length() const;
	cs_size_t Capacity() const;
	cs_bool ReadFrom(const cs_byte *pBuf, cs_size_t len);
	cs_bool ReadFrom(cs_cstring str);
	cs_bool WriteTo(cs_size_t len, cs_byte *&pBuf);
	cs_bool WriteToStr(cs_char *str, cs_size_t maxsize);

	// 回收掉已经废弃不用的内存
	cs_bool Collect();

	/// 写入二进制字节流
	template<typename T>
	cs_bool operator<<(T val);

	/// 从二进制字节流中写出
	template<typename T>
	cs_bool operator>>(T &val);

private:
	cs_bool Valid() const;
	cs_byte *GetTail() const; // 找到当前插入位置
	cs_bool Reserve(cs_size_t size);

	// 头指针，指向首元素，默认情况下指向-1
	int m_nHeadCursor;

	// 尾指针，指向末尾元素的下一位，默认情况下指向-1
	int m_nTailCursor;

	// 内存块
	CsBlock m_tBlock;
};

template<typename T>
cs_bool CsBytes_Ex::operator << (T val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t nSize = sizeof(T);
	cs_size_t nNewLen = Length() + nSize;
	if (nNewLen > Capacity())
	{
		if (!Reserve(nNewLen))
		{
			return false;
		}
	}
	memcpy(GetTail(), &val, nSize);
	m_nTailCursor += nSize;
	return true;
}

template<typename T>
cs_bool CsBytes_Ex::operator >> (T &val)
{
	cs_size_t nSize = sizeof(T);
	cs_int nNewLen = Length() - nSize;
	if (nNewLen < 0)
	{
		return false;
	}
	memcpy(&val, GetHead(), nSize);
	m_nHeadCursor += nSize;

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return true;
}

#endif // _CORE_BYTES_PRIVATE_H_