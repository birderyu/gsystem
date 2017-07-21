#include "gsystemexception.h"

namespace gsystem {

gsystemException::gsystemException() GNOEXCEPT
	: GException()
{

}

gsystemException::gsystemException(const GString &methodName, gsize lineNumber,
	const GString &fileName, const GStringList *whatArguments,
	const GString &whyMessageId, const GStringList *whyArguments) GNOEXCEPT
	: GException(methodName, lineNumber, fileName,
		whatArguments, whyMessageId, whyArguments)
{

}

gsystemException::~gsystemException()
{

}

}