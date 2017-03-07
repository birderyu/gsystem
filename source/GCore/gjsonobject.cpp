#include "gjsonobject.h"
#include "gstring.h"
#include "gliststack.h"
#include "gjsonpair.h"
#include "gjsonparsermessage.h"

GJsonObject::GJsonObject()
{

}

GJsonObject::GJsonObject(const GString &jsonStr)
{
	if (!Parse(jsonStr))
	{
		Dispose();
	}
}

GJsonObject::GJsonObject(const GJsonObject &jsonObj)
{

}

GJsonObject::~GJsonObject()
{
	Dispose();
}

gbool GJsonObject::Valid() const
{
	return !m_tJsonPairs.IsEmpty();
}

GString GJsonObject::ToString() const
{
	if (!Valid())
	{
		return GString();
	}

	GString jsonStr = "{";
	gsize size = m_tJsonPairs.Size();
	gsize pos = 0;
	for (GMap<GString, GJsonPair*>::ConstIterator citer = m_tJsonPairs.ConstBegin();
		citer != m_tJsonPairs.ConstEnd(); citer++)
	{
		if (!citer.Value())
		{
			return GString();
		}
		else
		{
			jsonStr += citer.Value()->ToString();
		}
		
		if (pos < size - 1)
		{
			jsonStr += ",";
		}
		pos++;
	}
	jsonStr += "}";
	return jsonStr;
}

gbool GJsonObject::Parse(const GString &jsonStr, gsize *cursor, GJsonParserMessage *msg)
{
	Dispose(); // 若已有数据，则先销毁
	GString parse_msg; // 如果发生了错误，返回可能的原因
	gsize _cursor = 0;
	if (cursor)
	{
		_cursor = *cursor;
	}

	// 字符栈
	// 两个字符将会入栈：'{'和','
	// 当遇到这两个字符，且符合规则时，二者入栈
	// 当遇到'}'且符合规则时，'{'出栈
	// 当一个JsonPair解析结束，且该JsonPair不是第一个时，','出栈
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
		else if (c == '{')
		{
			// 遇到'{'，说明应该开始解析JsonObject
			if (!char_stack.IsEmpty())
			{
				// '{'之前，栈中已经有数据，解析失败，直接退出
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

			//否则，'{'入栈
			char_stack.Push(c); // '{'入栈
		}
		else if (c == '}')
		{
			// 遇到'}'，解析结束，跳出循环，此时还不能判断是否已经解析成功
			char_stack.Pop(); // '{'出栈
			parse_msg = "非法的构造字符";
			break;
		}
		else if (c == ',')
		{
			// 遇到了','，说明已经解析过了至少一个JsonPair
			if (m_tJsonPairs.IsEmpty())
			{
				// 未遇到JsonPair就遇到了','，解析失败，直接退出
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
			// 遇到除此之外的任何字符，说明遇到了一个JsonPair
			GJsonPair *pair = new GJsonPair();
			if (!pair->Parse(jsonStr, &_cursor, msg))
			{
				// JsonPair解析失败，释放内存，直接退出
				if (cursor)
				{
					*cursor = _cursor;
				}
				delete pair;
				Dispose();
				return false;
			}

			if (!m_tJsonPairs.IsEmpty())
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
					delete pair;
					Dispose();
					return false;
				}
			}

			// 将解析成功的JsonPair加入JsonPairs
			m_tJsonPairs.Insert(pair->Key(), pair);
		}

		// 光标后移
		_cursor++;
	} // while

	// 是否解析成功
	gbool success = (char_stack.IsEmpty()) && (!m_tJsonPairs.IsEmpty());
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

gvoid GJsonObject::Dispose()
{
	for (GMap<GString, GJsonPair*>::Iterator iter = m_tJsonPairs.Begin();
		iter != m_tJsonPairs.End(); iter++)
	{
		if (iter.Value())
		{
			delete iter.Value();
		}
	}
	m_tJsonPairs.Clear();
}
