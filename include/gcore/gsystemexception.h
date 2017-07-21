#ifndef _CORE_SYSTEM_EXCEPTION_H_
#define _CORE_SYSTEM_EXCEPTION_H_

#include "gexception.h"

namespace gsystem {

class GAPI gsystemException
	: public GException
{
public:
	virtual ~gsystemException() = 0;
	static GExceptionPtr Create(std::exception &stdLibException,
		const GString &methodName, gsize lineNumber, const GString &fileName) GNOEXCEPT;

protected:
	gsystemException() GNOEXCEPT;
	gsystemException(const GString &methodName, gsize lineNumber,
		const GString &fileName, const GStringList *whatArguments,
		const GString &whyMessageId, const GStringList *whyArguments) GNOEXCEPT;
};

}



#endif // _CORE_SYSTEM_EXCEPTION_H_
