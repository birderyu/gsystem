#ifndef _CORE_STRING_EX_H_
#define _CORE_STRING_EX_H_

#include "CsGlobal_Ex.h"
#include <sstream>

class CsSmallStr_Ex;
class CsNormalStr_Ex;
class CsBigStr_Ex;
class CsRefStr_Ex;

// 根据32位做判断
#define CS_MIN_STRING_SIZE		8
#define CS_MAX_STRING_SIZE		20480

enum CS_STRING_EX_TYPE
{
	VALUE_STRING_SMALL = 0, // 值类型：小字符串，直接存储在数组中
	VALUE_STRING_NORMAL,	// 值类型：普通字符串，使用一块连续的内存存储
	VALUE_STRING_BIG,		// 值类型：大字符串，使用分段的内存存储
	REFERENCE_STRING = 99,	// 引用类型：来自于字符串池
};

// 小字符串
class CsSmallStr_Ex
{
public:
	static cs_size_t MaxSize();

public:
	cs_bool Initialize();
	cs_bool Initialize(cs_char cChar);
	cs_bool Initialize(const cs_char *pStr, cs_size_t len);
	cs_bool Initialize(const CsSmallStr_Ex &sStr);
	cs_size_t Length() const;
	cs_char GetAt(cs_size_t id) const;
	cs_cstring CString() const;

	cs_bool MakeTrim();
	cs_bool MakeTrimLeft();
	cs_bool MakeTrimRight();
	cs_bool MakeUpper();
	cs_bool MakeLower();

	cs_bool SwitchToNormal(CsNormalStr_Ex &) const;

private:
	cs_uint8 m_nLength;
	cs_char m_cStr[CS_MIN_STRING_SIZE];
};

// 普通型字符串
class CsNormalStr_Ex
{
public:
	static cs_size_t MaxSize();

public:
	cs_bool Initialize(const cs_char *pStr, cs_size_t len);
	cs_bool Initialize(const CsNormalStr_Ex &sStr);

	// 不安全的初始化
	// 不做拷贝操作，直接将指针替换为pStr
	// 若操作不当，会有很大风险
	// pStr的分配方式，必须与Free中的释放方式相对应
	cs_bool Initialize_Quick(cs_char *pStr, cs_size_t len);

	cs_size_t Length() const;
	cs_void Free();
	cs_char GetAt(cs_size_t id) const;
	cs_cstring CString() const;

	cs_bool MakeTrim();
	cs_bool MakeTrimLeft();
	cs_bool MakeTrimRight();
	cs_bool MakeUpper();
	cs_bool MakeLower();

	cs_bool CanSwithToSmall() const;
	cs_bool SwitchToSmall(CsSmallStr_Ex &) const;

private:
	cs_uint16 m_nLength;
	cs_char *m_pStr;
};

// 大字符串
class CsBigStr_Ex
{
private:
	cs_uint32 m_nLength;
	cs_pointer m_pStr;
};

// 引用型字符串
class CsRefStr_Ex
{
private:
	cs_uint32 m_nLength;
	cs_pointer m_pStr;
};

/****************************************************************************
**
** CsString.h
**
** @struct: CsStringStore
** @module: CsCore
** @brief:  字符串存储结构
**
** 字符串类型的存储结构，是一个联合（union）加一个标识字符串类型的变量
** 字符串类型采用如下的内存规则：
** 1.当字符个数极少时，采用栈内存，直接存储在对象中，提升读写效率，这样的字符串被称为“小字符串”；
** 2.当字符个数一般时，采用连续的堆内存，构建一块连续的存储空间，这样的字符串被称为“普通字符串”。
**   此时，一些对内存的扩展操作，如频繁地增加字符串的长度时，会有一定的效率损耗，
**   使用字符串构造类（CsStringBuilder）去构建一个字符串，以提升效率；
** 3.当字符串的个数极大时，采用不连续的堆内存，构建一个内存块的链表，这样的字符串被称为“大字符串”。
**   此时，字符串难以表示成一个C风格的字符串（CString），因为C风格的字符串是一个连续的存储空间；
** 4.此外，为了加快字符串的访问速度，使用一种引用结构（TODO）
**
****************************************************************************/
struct CsStringStore
{
	cs_byte m_nType;
	union
	{
		CsSmallStr_Ex	m_sSmallStr;	// 小字符串
		CsNormalStr_Ex	m_sNormalStr;	// 普通字符串
		CsBigStr_Ex		m_sBigStr;		// 大字符串
		CsRefStr_Ex		m_sRefStr;		// 引用字符串
	};

	static cs_void Free(CsStringStore &);
};

class CS_API CsString_Ex :public CsNewT<CsString_Ex>
{
public:
	// 
	template <typename T>
	static cs_bool FromNum(T nNum, cs_int nBase, CsString_Ex &sStr);

public:
	CsString_Ex();
	CsString_Ex(cs_char cChar);
	CsString_Ex(const cs_char *pStr);
	CsString_Ex(const CsString_Ex &sStr);
	~CsString_Ex();

	cs_bool Initialize();
	cs_bool Initialize(cs_char cChar);
	cs_bool Initialize(const cs_char *pStr);
	cs_bool Initialize(const CsString_Ex &sStr);

	// 引用型字符串，当进行写操作时，会转换为非引用型的字符串
	cs_bool IsReference() const;

	// 小字符串，可以直接拷贝，内存开销小
	cs_bool IsSmall() const;

	// 大字符串，不使用连续内存存储的字符串
	cs_bool IsLarge() const;

	// 使用连续内存存储的字符串
	cs_bool IsSerial() const;

	// 将引用类型转换成值类型
	CsString_Ex &ToValue();

	cs_char GetAt(cs_size_t id) const;
	cs_cstring CString() const;

	cs_size_t Length() const;
	cs_bool IsEmpty() const;

	CsString_Ex &MakeTrim();
	CsString_Ex &MakeTrimLeft();
	CsString_Ex &MakeTrimRight();

	CsString_Ex &MakeUpper();
	CsString_Ex &MakeLower();

	CsString_Ex &Replace(const cs_char *from, cs_size_t from_len, 
		const cs_char *to, cs_size_t to_len, 
		cs_bool bIsSensitive);
	CsString_Ex &Replace(cs_size_t start, cs_size_t length, 
		const cs_char *to, cs_size_t to_len, 
		cs_bool bIsSensitive);

	cs_uint64 HashCode() const;

	cs_bool operator==(const CsString_Ex &sStr) const
	{
		return false;
	}
	CsString_Ex &operator=(const CsString_Ex &sStr)
	{
		return *this;
	}
	CsString_Ex &operator+=(const CsString_Ex &sStr)
	{
		return *this;
	}
	
	//CsStringList Split(const CsString_Ex &sSep, cs_bool bIgnoreEmpty, cs_bool bIsSensitive) const;
	cs_int Find(cs_char c, cs_size_t start, cs_bool bIsSensitive) const;
	cs_int Find(const CsString_Ex &str, cs_size_t start, cs_bool bIsSensitive) const;
	CsString_Ex SubString(cs_size_t start, cs_size_t length);

	CsString_Ex &Switch(CS_STRING_EX_TYPE emType, cs_bool *pIsOk = NULL);

	// 根据长度计算字符串的类型
	CS_STRING_EX_TYPE GetTypeByLength(cs_size_t) const;

	// 回收内存
	CsString_Ex &Collect(cs_bool *pIsOk = NULL);
	
	template <typename T>
	T ToNum(cs_bool *isok = NULL) const;

private:
	cs_void Free();

	CsStringStore m_tStrMem;
};

template <typename T>
cs_bool CsString_Ex::FromNum(T nNum, cs_int nBase, CsString_Ex &sStr)
{
	std::ostringstream oss;
	if (nBase == 2)
	{

	}
	else if (nBase == 8)
	{
		oss << std::oct;
	}
	else if (nBase == 10)
	{
		oss << std::dec;
	}
	else if (nBase == 16)
	{
		oss << std::hex;
	}
	else
	{
		oss << std::dec;
	}
	oss << nNum;
	return sStr.Initialize(oss.str().c_str());
}

template <typename T>
T CsString_Ex::ToNum(cs_bool *isok) const
{
	std::istringstream iss(CString());
	T nNum;
	if (isok)
	{
		*isok = false;
	}
	if (iss >> nNum)
	{
		if (isok)
		{
			*isok = true;
		}
	}
	return nNum;
}

#endif // _CORE_STRING_EX_H_
