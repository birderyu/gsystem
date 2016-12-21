#include "CsTextDocument_Ex.h"
#include "CsTextDocument.h"

#define CS_TEXT_DOCUMNET_BUFFER_SIZE 4096

CsTextDocument_Ex::CsTextDocument_Ex(const CsString &sFileName)
: CsDocument_Ex(sFileName)
{

}

cs_void CsTextDocument_Ex::Flush()
{
	// TODO
}

cs_void CsTextDocument_Ex::Abort()
{
	// TODO
}

cs_bool CsTextDocument_Ex::ReadLine(CsString &line)
{
	if (!Valid() || !CanRead())
	{
		return false;
	}
	return false;
}

cs_bool CsTextDocument_Ex::WriteLine(const CsString &line, cs_int format)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}
	return false;
}

cs_cstring CsTextDocument_Ex::OpenMode() const
{
	switch (m_nOpenMode)
	{
	case CsDocument::NO_OPEN:
		return NULL;
	case CsDocument::ONLY_READ:
		return "rt";
	case CsDocument::ONLY_WIRTE:
		return "wt";
	case CsDocument::READ_WIRTE:
		return "rt+";
	case CsDocument::APPEND:
		return "at";
	default:
		break;
	}
	return NULL;
}

#undef CS_TEXT_DOCUMNET_BUFFER_SIZE
