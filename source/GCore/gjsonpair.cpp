#include "gjsonpair.h"
#include "gjsonvalue.h"
#include "gliststack.h"
#include "gjsonparsermessage.h"

GJsonPair::GJsonPair()
: m_pValue(GNULL)
{

}

GJsonPair::~GJsonPair()
{
	Dispose();
}

gbool GJsonPair::Valid() const
{
	return m_pValue != GNULL;
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

GString GJsonPair::ToString() const
{
	if (!Valid())
	{
		return GString();
	}

	GString jsonPair = "\"";
	jsonPair += m_sKey;
	jsonPair += "\":";
	jsonPair += m_pValue->ToString();
	return jsonPair;
}

gbool GJsonPair::Parse(const GString &jsonStr, gsize *cursor, GJsonParserMessage *msg)
{
	Dispose(); // 若已有数据，则先销毁
	GString parse_msg; // 如果发生了错误，返回可能的原因
	gsize _cursor = 0;
	if (cursor)
	{
		_cursor = *cursor;
	}

	gbool has_key = false;
	gsize key_start = GString::NULL_POS;

	while (true)
	{
		gchar c = jsonStr.GetAt(_cursor);
		if (c == '\0')
		{
			// 遇到字符串结束符，解析失败，直接退出
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (msg)
			{
				msg->SetIsSuccess(false);
				msg->SetErrorCursor(_cursor);
				msg->SetErrorMessage("字符串提前结束");
			}
			Dispose();
			return false;
		}
		else if (!G_CHAR_IS_ASCII(c))
		{
			// 遇到非法的字符，解析失败，直接退出
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (msg)
			{
				msg->SetIsSuccess(false);
				msg->SetErrorCursor(_cursor);
				msg->SetErrorMessage("非法的字符");
			}
			Dispose();
			return false;
		}
		else if (G_CHAR_IS_SPACE(c))
		{
			// 空白字符，不做任何操作
		}
		else if (c== '{' || c == '}' || 
			c == '[' || c == ']'||
			c == ',')
		{
			// 解析失败，直接退出
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (msg)
			{
				msg->SetIsSuccess(false);
				msg->SetErrorCursor(_cursor);
				msg->SetErrorMessage("非法的构造字符");
			}
			Dispose();
			return false;
		}
		else if (c == ':')
		{
			if (!has_key)
			{
				// 还没有解析完成Key就遇到了':'，解析失败，直接退出
				if (cursor)
				{
					*cursor = _cursor;
				}
				if (msg)
				{
					msg->SetIsSuccess(false);
					msg->SetErrorCursor(_cursor);
					msg->SetErrorMessage("非法的构造字符");
				}
				Dispose();
				return false;
			}
			else
			{
				// 已经解析了Key，说明应该解析JsonValue了
				_cursor++; // 先把光标后移，因为此时光标指向的是':'
				GJsonValue *value = new GJsonValue();
				if (!value->Parse(jsonStr, &_cursor, msg))
				{
					// JsonValue解析失败，释放内存，直接退出
					if (cursor)
					{
						*cursor = _cursor;
					}
					delete value;
					Dispose();
					return false;
				}

				// JsonValue解析成功，跳出循环
				m_pValue = value;
				break;
			}
		}
		else if (c == '"')
		{
			// 遇到了'"'，解析Key
			if (has_key)
			{
				// Key已被解析过，解析失败，直接退出
				if (cursor)
				{
					*cursor = _cursor;
				}
				if (msg)
				{
					msg->SetIsSuccess(false);
					msg->SetErrorCursor(_cursor);
					msg->SetErrorMessage("非法的构造字符");
				}
				Dispose();
				return false;
			}
			else
			{
				if (key_start == GString::NULL_POS)
				{
					// Key开始
					key_start = _cursor;
				}
				else
				{
					// Key结束，Key可以为空
					if (_cursor <= key_start)
					{
						// 解析失败，直接退出
						if (cursor)
						{
							*cursor = _cursor;
						}
						if (msg)
						{
							msg->SetIsSuccess(false);
							msg->SetErrorCursor(_cursor);
							msg->SetErrorMessage("非法的构造字符");
						}
						Dispose();
						return false;
					}

					// 解析名称，注意应该去除掉'"'
					m_sKey = jsonStr.SubString(key_start + 1, _cursor - key_start - 1);
					has_key = true;
				}
			}
		}
		else
		{
			// 其他字符串，不做任何操作
		}

		// 光标后移
		_cursor++;
	} // while

	gbool success = (m_pValue != GNULL);
	if (!success)
	{
		// 操作失败，清理内存
		Dispose();
	}

	if (cursor)
	{
		// 将当前光标写入消息
		*cursor = _cursor;
	}
	if (msg)
	{
		// 将信息写入消息
		msg->SetIsSuccess(success);
		if (!success)
		{
			msg->SetErrorCursor(_cursor);
			if (!parse_msg.IsEmpty())
			{
				msg->SetErrorMessage(parse_msg);
			}
			else
			{
				msg->SetErrorMessage("未知的原因");
			}
		}
	}
	return success;
}

gvoid GJsonPair::Dispose()
{
	if (m_pValue)
	{
		delete m_pValue;
	}
	m_pValue = GNULL;
}
