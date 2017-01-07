#include "gjsonpair.h"
#include "gjsonvalue.h"
#include "gliststack.h"

GJsonPair::GJsonPair()
: m_pValue(NULL)
{

}

GJsonPair::~GJsonPair()
{
	if (m_pValue)
	{
		delete m_pValue;
	}
}

gbool GJsonPair::Valid() const
{
	return m_pValue != NULL;
}

GString & GJsonPair::Key()
{
	return m_sKey;
}

const GString & GJsonPair::Key() const
{
	return m_sKey;
}

GJsonValue * GJsonPair::Value()
{
	return m_pValue;
}

const GJsonValue * GJsonPair::Value() const
{
	return m_pValue;
}

gbool GJsonPair::Parse(const GString &jsonStr, gsize cursor, GString *s_error)
{
	GListStack<gchar> stack;
	gbool has_key = false;

	gsize key_start = GString::NULL_POS;
	gsize value_start = GString::NULL_POS;

	GString parse_msg;

	do
	{
		gchar c = jsonStr.GetAt(cursor++);
		if (c == '\0')
		{
			// 遇到字符串结束符，跳出循环
			parse_msg = "字符串提前结束。";
			break;
		}

		if (G_CHAR_IS_SPACE(c))
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
				if (key_start == GString::NULL_POS)
				{
					break;
				}
				else
				{
					gsize key_size = cursor - key_start;
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
				if (value_start == GString::NULL_POS)
				{
					value_start = cursor - 1;
				}

				if (G_CHAR_IS_DIGIT(c))
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
			if (key_start == GString::NULL_POS)
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
