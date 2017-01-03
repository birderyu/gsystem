// JSON 数组在方括号中书写：
// 数组可包含多个对象：
// {
//		"employees":[
// 		{ "firstName":"John", "lastName" : "Doe" },
// 		{ "firstName":"Anna", "lastName" : "Smith" },
// 		{ "firstName":"Peter", "lastName" : "Jones" }
// 		]
// }
// 在上面的例子中，对象 "employees" 是包含三个对象的数组。每个对象代表一条关于某人（有姓和名）的记录。

#ifndef _CORE_JSON_ARRAY_H_
#define _CORE_JSON_ARRAY_H_

#include "CsJsonObject.h"
#include "CsList.h"
#include "CsVariant.h"

typedef CsList<CsVariant> CsVariantList;

class CS_API CsJsonArray
	: public CsJsonObject
{
public:
	CsJsonArray();
	CsJsonArray(const CsString &);
	CsJsonArray(const CsVariantList &);
	CsJsonArray(const CsJsonArray &);

private:
	CsString m_sKey;
	CsVariantList m_tValue;
};

#endif // _CORE_JSON_ARRAY_H_