#include "gssonobject.h"
#include "gstring.h"
#include "gliststack.h"
#include "gjsonpair.h"

GJsonObject::GJsonObject()
: m_bValid(true)
{

}

GJsonObject::GJsonObject(const GString &jsonStr)
: m_bValid(true)
{
	Parse(jsonStr);
}

GJsonObject::GJsonObject(const GJsonObject &jsonObj)
{

}

GJsonObject::~GJsonObject()
{

}

gbool GJsonObject::Parse(const GString &jsonStr, gsize cursor, GString *s_error)
{
	GListStack<gchar> char_stack;
	GString parse_msg;

	do 
	{
		gchar c = jsonStr.GetAt(cursor++);
		if (c == '\0')
		{
			// 遇到字符串结束符，跳出循环
			break;
		}

		if (G_CHAR_IS_SPACE(c))
		{
			// 如果是空白字符，则直接跳过
			continue;
		}

		// 否则，解析字符串
		if (c == '{')
		{
			char_stack.Push(c);
		}
		else if (c == '}')
		{
			char_stack.Pop();
			if (char_stack.IsEmpty())
			{
				// 
				break;
			}
		}
		else
		{
			// 遇到了第一个非空、非空白、非大括号的字符，说明遇到了第一个JsonPair
			GJsonPair *pair = new GJsonPair();
			if (!pair->Parse(jsonStr, cursor))
			{
				delete pair;
				break;
			}
			m_tJsonPairs.Insert(pair->Key(), pair);
		}
	} while (true);

	return !char_stack.IsEmpty();
}
