#include "goutofmemoryexception.h"

namespace gsystem {

GOutOfMemoryException::GOutOfMemoryException() GNOEXCEPT
	: gsystemException()
{

}

GOutOfMemoryException::GOutOfMemoryException(
	const GString &methodName, gsize lineNumber, 
	const GString &fileName, const GStringList *whatArguments,
	const GString &whyMessageId, const GStringList *whyArguments) GNOEXCEPT
	: gsystemException(methodName, lineNumber, fileName, 
		whatArguments, whyMessageId, whyArguments)
{

}

GOutOfMemoryException::~GOutOfMemoryException() GNOEXCEPT
{

}

gvoid GOutOfMemoryException::Raise()
{
	throw this;
}

}