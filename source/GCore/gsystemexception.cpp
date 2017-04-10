#include "gsystemexception.h"

namespace gsystem {

GSystemException::GSystemException() GNOEXCEPT
	: GException()
{

}

GSystemException::GSystemException(const GString &methodName, gsize lineNumber,
	const GString &fileName, const GStringList *whatArguments,
	const GString &whyMessageId, const GStringList *whyArguments) GNOEXCEPT
	: GException(methodName, lineNumber, fileName,
		whatArguments, whyMessageId, whyArguments)
{

}

GSystemException::~GSystemException()
{

}

}