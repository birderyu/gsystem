#include "CsJsonPair.h"
#include "CsJsonValue.h"
#include "CsListStack.h"

CsJsonPair::CsJsonPair()
: m_pValue(NULL)
{

}

CsJsonPair::~CsJsonPair()
{
	if (m_pValue)
	{
		delete m_pValue;
	}
}

cs_bool CsJsonPair::Valid() const
{
	return m_pValue != NULL;
}

CsString & CsJsonPair::Key()
{
	return m_sKey;
}

const CsString & CsJsonPair::Key() const
{
	return m_sKey;
}

CsJsonValue * CsJsonPair::Value()
{
	return m_pValue;
}

const CsJsonValue * CsJsonPair::Value() const
{
	return m_pValue;
}

cs_bool CsJsonPair::Parse(const CsString &jsonStr, cs_size_t cursor, CsString *s_error)
{
	CsListStack<cs_char> stack;
	cs_bool has_key = false;

	cs_size_t key_start = CsString::NULL_POS;
	cs_size_t value_start = CsString::NULL_POS;

	CsString parse_msg;

	do
	{
		cs_char c = jsonStr.GetAt(cursor++);
		if (c == '\0')
		{
			// 遇到字符串结束符，跳出循环
			parse_msg = "字符串提前结束。";
			break;
		}

		if (CS_CHAR_IS_SPACE(c))
		{
			// 如果是空白字符，则直接跳过
			continue;
		}

		// 否则，解析字符串
		if (!has_key)
		{
			// 还没有解析名称
			if (c == '\"')
			{

			}

			if (c == ':')
			{
				// 遇到了冒号，说明名称已经解析结束
				if (key_start == CsString::NULL_POS)
				{
					break;
				}
				else
				{
					cs_size_t key_size = cursor - key_start;
					if (key_size == 0)
					{
						parse_msg = "Json名称为空。";
					}
					break;

					m_sKey = jsonStr.SubString(key_start, cursor - key_start).Trim();
					has_key = true;
				}
			}
			else
			{
				if (value_start == CsString::NULL_POS)
				{
					value_start = cursor - 1;
				}

				if (CS_CHAR_IS_DIGIT(c))
				{
					// 有可能是Json数字，也有可能是错误的Json字符串
				}
				else if (c == 't' || c == 'f')
				{
					// 有可能是Json布尔型，也有可能是错误的Json字符串
				}
				else if (c == '\"')
				{
					// 有可能是Json字符串，也有可能是错误的Json字符串
				}
				else if (c == '[')
				{
					// 有可能是Json数组，也有可能是错误的Json字符串
				}
				else if (c == '{')
				{
					// 有可能是Json对象，也有可能是错误的Json字符串
				}
				else
				{
					// 有可能是JsonNull，也有可能是错误的Json字符串
				}
			}
		}
		else
		{
			// 已经解析完了名称
			if (key_start == CsString::NULL_POS)
			{
				key_start = cursor - 1;
			}
		}
	} while (true);

	if (!m_pValue)
	{
		if (s_error)
		{
			*s_error = "Json解析失败：" + parse_msg;
		}
		return false;
	}
	return true;
}
