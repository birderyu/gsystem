/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsJsonObject.h
** @brief	Json对象类型的定义
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		CsJsonObject
**
** Json对象在花括号中书写：
** 对象可以包含多个名称 / 值对：
** { "firstName": "John", "lastName": "Doe" }
**
****************************************************************************/

#ifndef _CORE_JSON_OBJECT_H_
#define _CORE_JSON_OBJECT_H_

#include "CsObject.h"
#include "CsString.h"
#include "CsMap.h"

class CsJsonPair;

class CS_API CsJsonObject
	: public CsNewT<CsJsonObject>
	, public CsObject
{
public:
	CsJsonObject();
	CsJsonObject(const CsString &jsonStr);
	CsJsonObject(const CsJsonObject &jsonObj);
	~CsJsonObject();

	cs_bool Valid() const;

	// 字符串解析，cursor为游标
	cs_bool Parse(const CsString &jsonStr, cs_size_t cursor = 0, CsString *s_error = NULL);

private:
	CsMap<CsString, CsJsonPair*> m_tJsonPairs;
	cs_bool m_bValid;
};

#endif // _CORE_JSON_OBJECT_H_