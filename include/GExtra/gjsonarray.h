/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file gjsonarray.h
** @brief Json数组
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-3
** @version 0.5.0
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

namespace gsystem { // gsystem
	namespace json { // gsystem.json
		class GJsonValue;
		class GJsonParserMessage;
	} // namespace gsystem.json
} // namespace gsystem

namespace gsystem { // gsystem
namespace json { // gsystem.json

class GAPI GJsonArray
	: public GObject
{
	friend class GJsonObject;

public:
	GJsonArray();
	~GJsonArray();

	gbool Valid() const;

	GString ToString() const;

	gbool Parse(const GString &jsonStr, gsize *cursor = GNULL, GJsonParserMessage *msg = GNULL);

private:
	gbool Parse(const GString &jsonStr, gsize *cursor);
	gvoid Destroy();
	GList<GJsonValue*> m_tJsonValues;
};

} // namespace gsystem.json
} // namespace gsystem

#endif // _CORE_JSON_ARRAY_H_