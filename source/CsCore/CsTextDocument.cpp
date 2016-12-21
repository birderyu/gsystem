#include "CsTextDocument.h"
#include "CsTextDocument_Ex.h"

CsTextDocument::CsTextDocument(const CsString &sFileName)
: CsDocument(new CsTextDocument_Ex(sFileName))
{

}

CsTextDocument::CsTextDocument(CsTextDocument_Ex *pTextFile_Ex)
: CsDocument(pTextFile_Ex)
{

}

cs_bool CsTextDocument::Read(cs_size_t size, CsString &)
{
	// TODO
	return false;
}

cs_bool CsTextDocument::ReadAll(CsString &)
{
	// TODO
	return false;
}

cs_bool CsTextDocument::Write(const CsString &)
{
	// TODO
	return false;
}

cs_bool CsTextDocument::ReadLine(CsString &)
{
	// TODO
	return false;
}

cs_bool CsTextDocument::WriteLine(const CsString &)
{
	// TODO
	return false;
}
