/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @author	Birderyu
** @contact	https://github.com/birderyu
** @file	CsString.h
** @date	2016-12-03
** @brief	字符串类型的定义
**
****************************************************************************/

#ifndef _CORE_STRING_H_
#define _CORE_STRING_H_

#include "CsObject.h"
#include "CsStructure.h"
#include "CsStringStore.h"
#include <string>

class CsStringList;

/****************************************************************************
**
** CsString.h
**
** @class	CsString
** @module	CsCore
** @brief	字符串类型
**
** 提供基础的字符串类型，该类不可以被继承（final）。
**		字符串的实现类位于字符串实现类（CsString_Ex）中，它是一个私有实现类，对于库的使用
** 者和开发者，可以不用关心该类的具体实现细节。
**		本类采用写时拷贝（Copy-on-Write）的思想，使用一个共享指针（CsSharedPointer）[2]
** 存储具体字符串的指针，这是一个带有引用计数器的智能指针。当执行字符串拷贝操作时，加一个引用
** 计数，源字符串和拷贝字符串共同享有一份资源。当进行读操作时，使用共享资源；当进行写操作时，
** 若当前对象的资源被共享，则会拷贝一个新的实例，随后对新的实例进行写操作，推迟真正拷贝资源的
** 时间。
**
** @see	CsString_Ex
** @see	CsSharedPointer
**
****************************************************************************/
class CS_API CsString final 
	: public CsListT<CsString>
	, public CsObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_STRING, };

public:
	class Iterator
	{

	};

public:
	static CsString FromNum(cs_small nNum, cs_int nBase = 10);
	static CsString FromNum(cs_usmall nNum, cs_int nBase = 10);
	static CsString FromNum(cs_short nNum, cs_int nBase = 10);
	static CsString FromNum(cs_ushort nNum, cs_int nBase = 10);
	static CsString FromNum(cs_int nNum, cs_int nBase = 10);
	static CsString FromNum(cs_uint nNum, cs_int nBase = 10);
	static CsString FromNum(cs_long nNum, cs_int nBase = 10);
	static CsString FromNum(cs_ulong nNum, cs_int nBase = 10);
	static CsString FromNum(cs_longlong nNum, cs_int nBase = 10);
	static CsString FromNum(cs_ulonglong nNum, cs_int nBase = 10);
	static CsString FromNum(cs_float nNum, cs_int nBase = 10);
	static CsString FromNum(cs_double nNum, cs_int nBase = 10);
	static CsString FromNum(cs_decimal nNum, cs_int nBase = 10);

	static CsString FromStdString(const std::string &sStr);

public:
	/****************************************************************************
	**
	** CsString
	**
	** @name	CsString
	** @brief	构造函数（constructor）
	**
	****************************************************************************/
	CsString();
	CsString(cs_char cChar);
	CsString(const cs_char *pStr);
	CsString(const CsString &sStr);
	~CsString();

	cs_size_t Size() const;
	cs_bool Resize(cs_size_t);

	cs_char GetAt(cs_size_t pos) const;
	cs_char &GetAt(cs_size_t pos);

	const cs_char *Cursor(cs_size_t pos) const;
	cs_char *Cursor(cs_size_t pos);

	cs_bool Equals(const CsString &, cs_bool bIsSensitive = true) const;

	cs_bool StartWith(cs_char c) const;
	cs_bool EndWith(cs_char c) const;

	friend CS_API CsString operator+(const CsString &s1, const CsString &s2);

	/// 运算符重载
	cs_bool operator==(const CsString &sStr) const;
	CsString &operator=(const CsString &sStr);
	CsString &operator+=(const CsString &sStr);
	cs_char operator[](cs_size_t) const;
	cs_char &operator[](cs_size_t);

	cs_small ToSmall(cs_bool *bIsOk = NULL) const;
	cs_usmall ToUSmall(cs_bool *bIsOk = NULL) const;
	cs_short ToShort(cs_bool *bIsOk = NULL) const;
	cs_ushort ToUShort(cs_bool *bIsOk = NULL) const;
	cs_int ToInt(cs_bool *bIsOk = NULL) const;
	cs_uint ToUInt(cs_bool *bIsOk = NULL) const;
	cs_long ToLong(cs_bool *bIsOk = NULL) const;
	cs_ulong ToULong(cs_bool *bIsOk = NULL) const;
	cs_longlong ToLongLong(cs_bool *bIsOk = NULL) const;
	cs_ulonglong ToULongLong(cs_bool *bIsOk = NULL) const;
	cs_float ToFloat(cs_bool *bIsOk = NULL) const;
	cs_double ToDouble(cs_bool *bIsOk = NULL) const;
	cs_decimal ToDecimal(cs_bool *bIsOk = NULL) const;

	cs_bool IsEmpty() const;

	CsString Trim() const;
	CsString TrimLeft() const;
	CsString TrimRight() const;

	CsString ToUpper() const;
	CsString ToLower() const;
	cs_cstring CString() const;
	CsString &Replace(const CsString &from, const CsString &to, cs_bool bIsSensitive = true);
 
	// bIgnoreEmpty：是否忽略空格
	// bIsSensitive：大小写是否敏感
	CsStringList Split(const CsString &sSep, cs_bool bIgnoreEmpty = false, cs_bool bIsSensitive = true) const;
	cs_size_t Find(cs_char c, cs_size_t start = 0, cs_bool bIsSensitive = true) const;
	cs_size_t Find(const CsString &str, cs_size_t start = 0, cs_bool bIsSensitive = true) const;

	CsString SubString(cs_size_t start, cs_size_t length) const;

	// 继承自Object的方法
	const CsObject *Boxing() const;
	cs_uint ClassCode() const;
	CsString ToString() const;
	CsString Format() const;

private:
	cs_bool IsReference() const;
	cs_void Free();
	CsString &ToValue();
	CsStringStore::TYPE GetTypeBySize(cs_size_t) const;
	cs_bool Switch(CsStringStore::TYPE);

	CsStringStore m_tStringStore;
};

CS_API CsString operator+(const CsString &s1, const CsString &s2);

#endif // _CORE_STRING_H_
