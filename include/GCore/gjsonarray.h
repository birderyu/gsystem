/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gjsonarray.h
** @brief	Json数组类型的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		GJsonArray
**
** Json数组在方括号中书写：
** 数组可包含多个对象：
** {
**	"employees":[
**		{ "firstName":"John", "lastName" : "Doe" },
** 		{ "firstName":"Anna", "lastName" : "Smith" },
** 		{ "firstName":"Peter", "lastName" : "Jones" }
**	]
** }
** 在上面的例子中，对象 "employees" 是包含三个对象的数组，每个对象
** 代表一条关于某人（有姓和名）的记录。
**
****************************************************************************/

#ifndef _CORE_JSON_ARRAY_H_
#define _CORE_JSON_ARRAY_H_

#include "glist.h"

G_BEGIN_NAMESPACE
class GJsonValue;
class GJsonParserMessage;
G_END_NAMESPACE

G_BEGIN_NAMESPACE

class GAPI GJsonArray
	: public GObject
{
public:
	GJsonArray();
	~GJsonArray();

	gbool Valid() const;

	GString ToString() const;

	gbool Parse(const GString &jsonStr, gsize *cursor = GNULL, GJsonParserMessage *msg = GNULL);

private:
	gvoid Dispose();
	GList<GJsonValue*> m_tJsonValues;
};

G_END_NAMESPACE

#endif // _CORE_JSON_ARRAY_H_