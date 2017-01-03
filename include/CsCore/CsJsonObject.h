// JSON 对象
// JSON 对象在花括号中书写：
// 对象可以包含多个名称 / 值对：
// { "firstName": "John", "lastName": "Doe" }

#ifndef _CORE_JSON_OBJECT_H_
#define _CORE_JSON_OBJECT_H_

#include "CsObject.h"
#include "CsStructure.h"

// 一个Json对象
class CS_API CsJsonObject
	: public CsPreviousNextNodeT<CsJsonObject>
	, public CsChildNodeT<CsJsonObject>
	, public CsNewT<CsJsonObject>
	, public CsObject
{
public:
	enum TYPE
	{
		JSON_OBJECT,	// 容器
		JSON_VALUE,		// 键值对
		JSON_ARRAY,		// 数组
	};

public:
	CsJsonObject();
	CsJsonObject(const CsJsonObject &);

	virtual ~CsJsonObject();

	virtual TYPE Type();
};

#endif // _CORE_JSON_OBJECT_H_