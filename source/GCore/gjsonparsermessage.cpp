#include "gjsonparsermessage.h"

namespace gnova { // gnova
namespace json { // gnova.json

gbool GJsonParserMessage::IsSuccess() const
{
	return m_bSuccess;
}

gsize GJsonParserMessage::ErrorCursor() const
{
	return m_nErrorCursor;
}

const GString &GJsonParserMessage::ErrorMessage() const
{
	return m_sErrorMessage;
}

gvoid GJsonParserMessage::SetIsSuccess(gbool success)
{
	m_bSuccess = success;
}

gvoid GJsonParserMessage::SetErrorCursor(gsize cursor)
{
	m_nErrorCursor = cursor;
}

gvoid GJsonParserMessage::SetErrorMessage(const GString &msg)
{
	m_sErrorMessage = msg;
}

} // namespace gnova.json
} // namespace gnova