#ifndef _CORE_JSON_PARSER_MESSAGE_H_
#define _CORE_JSON_PARSER_MESSAGE_H_

#include "gobject.h"
#include "gstring.h"

namespace gnova {
namespace json {

class GAPI GJsonParserMessage
{
public:
	gbool IsSuccess() const;
	gsize ErrorCursor() const;
	const GString &ErrorMessage() const;

	gvoid SetIsSuccess(gbool success);
	gvoid SetErrorCursor(gsize cursor);
	gvoid SetErrorMessage(const GString &msg);

private:
	gbool m_bSuccess;
	gsize m_nErrorCursor;
	GString m_sErrorMessage;
};

}
}

#endif // _CORE_JSON_PARSER_MESSAGE_H_