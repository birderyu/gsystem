#ifndef _CORE_OUT_OF_MEMORY_EXCEPTION_H_
#define _CORE_OUT_OF_MEMORY_EXCEPTION_H_

#include "gsystemexception.h"

namespace gsystem {

class GAPI GOutOfMemoryException
	: public gsystemException
{
public:
	GOutOfMemoryException(const GString &methodName, gsize lineNumber,
		const GString &fileName, const GStringList *whatArguments,
		const GString &whyMessageId, const GStringList *whyArguments) GNOEXCEPT;
	virtual ~GOutOfMemoryException() GNOEXCEPT;

protected:
	GOutOfMemoryException() GNOEXCEPT;
	gvoid Raise();
};

}



#endif // _CORE_OUT_OF_MEMORY_EXCEPTION_H_
