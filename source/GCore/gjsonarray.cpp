#include "gjsonarray.h"
#include "gjsonvalue.h"
#include "gjsonparsermessage.h"
#include "gliststack.h"

GJsonArray::GJsonArray()
{

}

GJsonArray::~GJsonArray()
{
	Dispose();
}

gbool GJsonArray::Valid() const
{
	return !m_tJsonValues.IsEmpty();
}

GString GJsonArray::ToString() const
{
	if (!Valid())
	{
		return GString();
	}

	GString jsonArr = "[";
	gsize size = m_tJsonValues.Size();
	gsize pos = 0;
	for (GList<GJsonValue*>::ConstIterator citer = m_tJsonValues.ConstBegin();
		citer != m_tJsonValues.ConstEnd(); citer++)
	{
		if (!*citer)
		{
			return GString();
		}
		else
		{
			jsonArr += (*citer)->ToString();
		}

		if (pos < size - 1)
		{
			jsonArr += ",";
		}
		pos++;
	}
	jsonArr += "]";
	return jsonArr;
}

gbool GJsonArray::Parse(const GString &jsonStr, gsize *cursor, GJsonParserMessage *msg)
{
	Dispose(); // 若已有数据，则先销毁
	GString parse_msg; // 如果发生了错误，返回可能的原因
	gsize _cursor = 0;
	if (cursor)
	{
		_cursor = *cursor;
	}

	// 字符栈
	// 两个字符将会入栈：'['和','
	// 当遇到这两个字符，且符合规则时，二者入栈
	// 当遇到']'且符合规则时，'['出栈
	// 当一个JsonValue解析结束，且该JsonValue不是第一个时，','出栈
	GListStack<gchar> char_stack;

	// 循环解析
	while (true)
	{
		gchar c = jsonStr.GetAt(_cursor); // 获取一个字符

		if (c == '\0')
		{
			// 遇到字符串结束符，跳出循环，此时还不能判断是否已经解析成功
			parse_msg = "字符串提前结束";
			break;
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
		else if (c == '[')
		{
			// 遇到'['，说明应该开始解析JsonArray
			if (!char_stack.IsEmpty())
			{
				// '['之前，栈中已经有数据，解析失败，直接退出
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

			//否则，'['入栈
			char_stack.Push(c); // '['入栈
		}
		else if (c == ']')
		{
			// 遇到']'，解析结束，跳出循环，此时还不能判断是否已经解析成功
			char_stack.Pop(); // '['出栈
			parse_msg = "非法的构造字符";
			break;
		}
		else if (c == ',')
		{
			// 遇到了','，说明已经解析过了至少一个JsonValue
			if (m_tJsonValues.IsEmpty())
			{
				// 未遇到JsonValue就遇到了','，解析失败，直接退出
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

			//否则，','入栈
			char_stack.Push(c); // ','入栈
		}
		else
		{
			// 遇到除此之外的任何字符，说明遇到了一个JsonValue
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

			if (!m_tJsonValues.IsEmpty())
			{
				gchar _c = '\0';
				char_stack.Pop(&_c); // ','出栈
				if (_c != ',')
				{
					// 解析失败，释放内存，直接退出
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
					delete value;
					Dispose();
					return false;
				}
			}

			// 将解析成功的JsonPair加入JsonPairs
			m_tJsonValues.PushBack(value);
		}
		// 光标后移
		_cursor++;
	} // while

	// 是否解析成功
	gbool success = (char_stack.IsEmpty()) && (!m_tJsonValues.IsEmpty());
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

gvoid GJsonArray::Dispose()
{
	for (GList<GJsonValue*>::Iterator iter = m_tJsonValues.Begin();
		iter != m_tJsonValues.End(); iter++)
	{
		if (*iter)
		{
			delete *iter;
		}
	}
	m_tJsonValues.Clear();
}
