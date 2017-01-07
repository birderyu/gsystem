/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gjsonobject.h
** @brief	Json对象类型的定义
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		GJsonObject
**
** Json对象在花括号中书写：
** 对象可以包含多个名称 / 值对：
** { "firstName": "John", "lastName": "Doe" }
**
****************************************************************************/

#ifndef _CORE_JSON_OBJECT_H_
#define _CORE_JSON_OBJECT_H_

#include "gobject.h"
#include "gstring.h"
#include "gmap.h"

class GJsonPair;

class GAPI GJsonObject
	: public GNewT<GJsonObject>
	, public GObject
{
public:
	GJsonObject();
	GJsonObject(const GString &jsonStr);
	GJsonObject(const GJsonObject &jsonObj);
	~GJsonObject();

	gbool Valid() const;

	// 字符串解析，cursor为游标
	gbool Parse(const GString &jsonStr, gsize cursor = 0, GString *s_error = NULL);

private:
	GMap<GString, GJsonPair*> m_tJsonPairs;
	gbool m_bValid;
};

#endif // _CORE_JSON_OBJECT_H_