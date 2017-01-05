/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsJsonValue.h
** @brief	Json值类型的定义
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		CsJsonValue
**
** Json值可以是:
** 整型：Integer
** 浮点型：Float
** 字符串：String
** 布尔型：Boolean
** 数组：Array
** 对象：Object
** Null
**
****************************************************************************/

#ifndef _CORE_JSON_VALUE_H_
#define _CORE_JSON_VALUE_H_

#include "CsObject.h"

class CS_API CsJsonValue
	: public CsObject
{
public:
	enum JSON_VALUE_TYPE
	{
		JSON_VALUE_TYPE_NULL,
		JSON_VALUE_TYPE_BOOLEAN,
		JSON_VALUE_TYPE_INTEGER,
		JSON_VALUE_TYPE_FLOAT,
		JSON_VALUE_TYPE_STRING,
		JSON_VALUE_TYPE_ARRAY,
		JSON_VALUE_TYPE_OBJECT,
	};

public:
	virtual ~CsJsonValue();
	virtual JSON_VALUE_TYPE Type() const;
};

#endif // _CORE_JSON_VALUE_H_