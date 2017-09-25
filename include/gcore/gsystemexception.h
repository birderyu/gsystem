#ifndef _CORE_SYSTEM_EXCEPTION_H_
#define _CORE_SYSTEM_EXCEPTION_H_

#include "gexception.h"

namespace gsystem {

class GAPI GSystemException
	: public GException
{
public:
	virtual ~GSystemException() = 0;
	static GExceptionPtr Create(std::exception &exception,
		const GString &methodName, gsize lineNumber, const GString &fileName) GNOEXCEPT;

protected:
	GSystemException() GNOEXCEPT;
	GSystemException(const GString &methodName, gsize lineNumber,
		const GString &fileName, const GStringList *whatArguments,
		const GString &whyMessageId, const GStringList *whyArguments) GNOEXCEPT;
};

}



#endif // _CORE_SYSTEM_EXCEPTION_H_
