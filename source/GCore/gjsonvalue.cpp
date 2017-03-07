#include "gjsonvalue.h"
#include "gjsonobject.h"
#include "gjsonarray.h"
#include "gjsonparsermessage.h"

GJsonValue::GJsonValue()
: m_nType(JSON_VALUE_TYPE_ILLEGAL)
{

}

GJsonValue::~GJsonValue()
{
	Dispose();
}

gbool GJsonValue::Valid()
{
	if (m_nType == JSON_VALUE_TYPE_ILLEGAL)
	{
		return false;
	}
	return true;
}

GString GJsonValue::ToString() const
{
	switch (m_nType)
	{
	case JSON_VALUE_TYPE_ILLEGAL:
		break;
	case JSON_VALUE_TYPE_NULL:
		return GString("null");
		break;
	case JSON_VALUE_TYPE_BOOLEAN:
	case JSON_VALUE_TYPE_NUMBER:
		return m_tValue.ToString();
		break;
	case JSON_VALUE_TYPE_STRING:
	{
		GString s = "\"";
		s += m_tValue.ToString();
		s += "\"";
		return s;
	}
		break;
	case JSON_VALUE_TYPE_ARRAY:
	{
		if (m_tValue.GetType() != GVariety::VARIETY_TYPE_POINTER)
		{
			return GString();
		}
		gpointer ptr = m_tValue.GetPoiter();
		if (!ptr)
		{
			return GString();
		}
		return ((GJsonArray*)ptr)->ToString();
	}
		break;
	case JSON_VALUE_TYPE_OBJECT:
	{
		if (m_tValue.GetType() != GVariety::VARIETY_TYPE_POINTER)
		{
			return GString();
		}
		gpointer ptr = m_tValue.GetPoiter();
		if (!ptr)
		{
			return GString();
		}
		return ((GJsonObject*)ptr)->ToString();
	}
		break;
	default:
		break;
	}
	return GString();
}

gbool GJsonValue::Parse(const GString &jsonStr, gsize *cursor, GJsonParserMessage *msg)
{
	Dispose(); // 若已有数据，则先销毁
	gsize _cursor = 0;
	if (cursor)
	{
		_cursor = *cursor;
	}

	while (true)
	{
		gchar c = jsonStr.GetAt(_cursor);
		if (G_CHAR_IS_SPACE(c))
		{
			// 空白字符，不做任何操作
		}
		else if (G_CHAR_IS_DIGIT(c))
		{
			// 有可能是Json数字，也有可能是错误的Json字符串
			gbool success = Parse_Number(jsonStr, _cursor, msg);
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (!success)
			{
				Dispose();
			}
			return success;
		}
		else if (c == 't' || c == 'f')
		{
			// 有可能是Json布尔型，也有可能是错误的Json字符串
			gbool success = Parse_Boolean(jsonStr, _cursor, msg);
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (!success)
			{
				Dispose();
			}
			return success;
		}
		else if (c == '\"')
		{
			// 有可能是Json字符串，也有可能是错误的Json字符串
			gbool success = Parse_String(jsonStr, _cursor, msg);
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (!success)
			{
				Dispose();
			}
			return success;
		}
		else if (c == '[')
		{
			// 有可能是Json数组，也有可能是错误的Json字符串
			gbool success = Parse_Array(jsonStr, _cursor, msg);
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (!success)
			{
				Dispose();
			}
			return success;
		}
		else if (c == '{')
		{
			// 有可能是Json对象，也有可能是错误的Json字符串
			gbool success = Parse_Object(jsonStr, _cursor, msg);
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (!success)
			{
				Dispose();
			}
			return success;
		}
		else if (c == 'n')
		{
			// 有可能是JsonNull，也有可能是错误的Json字符串
			gbool success = Parse_Null(jsonStr, _cursor, msg);
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (!success)
			{
				Dispose();
			}
			return success;
		}
		else
		{
			// 其他字符一律算解析失败，直接退出
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

		// 光标后移
		_cursor++;
	} // while
}

gbool GJsonValue::Parse_Number(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg)
{
	gsize start_cursor(cursor); // 记录下最开始的位置
	gbool has_float = false; // 是否包含了小数点

	while (true)
	{
		gchar c = jsonStr.GetAt(cursor);
		if (G_CHAR_IS_SPACE(c) || c == ',' || c == '}' || c == ']')
		{
			if (cursor <= start_cursor)
			{
				// 解析失败，直接退出
				if (msg)
				{
					msg->SetIsSuccess(false);
					msg->SetErrorCursor(cursor);
					msg->SetErrorMessage("非法的字符");
				}
				return false;
			}

			GString sNumber = jsonStr.SubString(start_cursor, cursor - start_cursor);
			if (has_float)
			{
				gbool is_ok = false;
				gdouble n = sNumber.ToDouble(&is_ok);
				if (!is_ok)
				{
					// 解析失败，直接退出
					if (msg)
					{
						msg->SetIsSuccess(false);
						msg->SetErrorCursor(cursor);
						msg->SetErrorMessage("非法的字符");
					}
				}
				// 解析成功
				m_nType = JSON_VALUE_TYPE_NUMBER;
				m_tValue.SetValue(n);
				break;
			}
			else
			{
				gbool is_ok = false;
				gint n = sNumber.ToInt(&is_ok);
				if (!is_ok)
				{
					// 解析失败，直接退出
					if (msg)
					{
						msg->SetIsSuccess(false);
						msg->SetErrorCursor(cursor);
						msg->SetErrorMessage("非法的字符");
					}
				}
				// 解析成功
				m_nType = JSON_VALUE_TYPE_NUMBER;
				m_tValue.SetValue(n);
				break;
			}
		}
		else if (c == '.')
		{
			if (cursor <= start_cursor || has_float)
			{
				// 解析失败，直接退出
				if (msg)
				{
					msg->SetIsSuccess(false);
					msg->SetErrorCursor(cursor);
					msg->SetErrorMessage("非法的字符");
				}
				return false;
			}
			has_float = true;
		}
		else
		{
			// 不做任何操作
		}

		// 光标后移
		cursor++;
	} // while

	if (m_nType = JSON_VALUE_TYPE_NUMBER)
	{
		// 解析成功，光标回退
		cursor--;
		return true;
	}
	else
	{
		// 解析失败
		if (msg)
		{
			msg->SetIsSuccess(false);
			msg->SetErrorCursor(cursor);
			msg->SetErrorMessage("非法的字符");
		}
	}
	return false;
}

gbool GJsonValue::Parse_Boolean(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg)
{
	if (jsonStr.GetAt(cursor) == 'f')
	{
		if (jsonStr.GetAt(++cursor) == 'a' &&
			jsonStr.GetAt(++cursor) == 'l' &&
			jsonStr.GetAt(++cursor) == 's' &&
			jsonStr.GetAt(++cursor) == 'e')
		{
			m_nType = JSON_VALUE_TYPE_BOOLEAN;
			m_tValue.SetValue(false);
			return true;
		}
		else
		{
			if (msg)
			{
				msg->SetIsSuccess(false);
				msg->SetErrorCursor(cursor);
				msg->SetErrorMessage("非法的字符");
			}
			return false;
		}
	}
	else if (jsonStr.GetAt(cursor) == 't')
	{
		if (jsonStr.GetAt(++cursor) == 'r' &&
			jsonStr.GetAt(++cursor) == 'u' &&
			jsonStr.GetAt(++cursor) == 'e')
		{
			m_nType = JSON_VALUE_TYPE_BOOLEAN;
			m_tValue.SetValue(true);
			return true;
		}
		else
		{
			if (msg)
			{
				msg->SetIsSuccess(false);
				msg->SetErrorCursor(cursor);
				msg->SetErrorMessage("非法的字符");
			}
		}
		return false;
	}
	else
	{
		if (msg)
		{
			msg->SetIsSuccess(false);
			msg->SetErrorCursor(cursor);
			msg->SetErrorMessage("非法的字符");
		}
		return false;
	}

	return m_nType == JSON_VALUE_TYPE_BOOLEAN;
}

gbool GJsonValue::Parse_String(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg)
{
	gsize start_cursor(cursor); // 记录下最开始的位置
	gbool has_begin = false;

	while (true)
	{
		gchar c = jsonStr.GetAt(cursor);
		if (c == '\"')
		{
			if (!has_begin)
			{
				start_cursor = cursor;
				has_begin = true;
			}
			else
			{
				if (cursor <= start_cursor)
				{
					// 解析失败，直接退出
					if (msg)
					{
						msg->SetIsSuccess(false);
						msg->SetErrorCursor(cursor);
						msg->SetErrorMessage("非法的字符");
					}
					return false;
				}
				GString s = jsonStr.SubString(start_cursor + 1, cursor - start_cursor - 1);
				m_nType = JSON_VALUE_TYPE_STRING;
				m_tValue.SetValue(s);
				break;
			}
		}
		else
		{
			if (!has_begin)
			{
				// 解析失败，直接退出
				if (msg)
				{
					msg->SetIsSuccess(false);
					msg->SetErrorCursor(cursor);
					msg->SetErrorMessage("非法的字符");
				}
				return false;
			}
		}

		// 光标后移
		cursor++;
	} // while

	return m_nType == JSON_VALUE_TYPE_STRING;
}

gbool GJsonValue::Parse_Array(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg)
{
	GJsonArray *arr = new GJsonArray();
	if (!arr->Parse(jsonStr, &cursor, msg))
	{
		return false;
	}
	m_tValue.SetPoiter(arr);
	m_nType = JSON_VALUE_TYPE_ARRAY;
	return true;
}

gbool GJsonValue::Parse_Object(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg)
{
	GJsonObject *obj = new GJsonObject();
	if (!obj->Parse(jsonStr, &cursor, msg))
	{
		return false;
	}
	m_tValue.SetPoiter(obj);
	m_nType = JSON_VALUE_TYPE_OBJECT;
	return true;
}

gbool GJsonValue::Parse_Null(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg)
{
	if (jsonStr.GetAt(cursor) == 'n' &&
		jsonStr.GetAt(++cursor) == 'u' &&
		jsonStr.GetAt(++cursor) == 'l' &&
		jsonStr.GetAt(++cursor) == 'l')
	{
		m_nType = JSON_VALUE_TYPE_NULL;
		return true;
	}
	else
	{
		if (msg)
		{
			msg->SetIsSuccess(false);
			msg->SetErrorCursor(cursor);
			msg->SetErrorMessage("非法的字符");
		}
		return false;
	}

	return m_nType == JSON_VALUE_TYPE_NULL;
}

gvoid GJsonValue::Dispose()
{
	if (m_tValue.GetType() == GVariety::VARIETY_TYPE_POINTER)
	{
		gpointer ptr = m_tValue.GetPoiter();
		if (!ptr)
		{
			return;
		}

		if (m_nType == JSON_VALUE_TYPE_ARRAY)
		{
			GJsonObject *obj = (GJsonObject *)ptr;
			delete obj;
		}
		else if (m_nType == JSON_VALUE_TYPE_OBJECT)
		{
			GJsonArray *arr = (GJsonArray *)ptr;
			delete arr;
		}

		m_tValue.SetPoiter(GNULL);
	}

	m_nType = JSON_VALUE_TYPE_ILLEGAL;
}
