#include "CsJsonObject.h"
#include "CsString.h"
#include "CsListStack.h"
#include "CsJsonPair.h"

CsJsonObject::CsJsonObject()
: m_bValid(true)
{

}

CsJsonObject::CsJsonObject(const CsString &jsonStr)
: m_bValid(true)
{
	Parse(jsonStr);
}

CsJsonObject::CsJsonObject(const CsJsonObject &jsonObj)
{

}

CsJsonObject::~CsJsonObject()
{

}

cs_bool CsJsonObject::Parse(const CsString &jsonStr, cs_size_t cursor, CsString *s_error)
{
	CsListStack<cs_char> char_stack;
	CsString parse_msg;

	do 
	{
		cs_char c = jsonStr.GetAt(cursor++);
		if (c == '\0')
		{
			// 遇到字符串结束符，跳出循环
			break;
		}

		if (CS_CHAR_IS_SPACE(c))
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
			CsJsonPair *pair = new CsJsonPair();
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
