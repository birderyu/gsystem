#include "gtextfile.h"
#include "CsTextFile_Ex.h"

GTextFile::GTextFile(const GString &sFileName)
: GFile(new CsTextFile_Ex(sFileName))
{

}

GTextFile::GTextFile(CsTextFile_Ex *pTextFile_Ex)
: GFile(pTextFile_Ex)
{

}

gbool GTextFile::Read(gsize size, GString &str)
{
	GASSERT(m_pFileEx);
	CsTextFile_Ex *pTextFile_Ex = (CsTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Read(size, str);
}

gbool GTextFile::ReadAll(GString &str)
{
	GASSERT(m_pFileEx);
	CsTextFile_Ex *pTextFile_Ex = (CsTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->ReadAll(str);
}

gbool GTextFile::Write(const GString &str)
{
	GASSERT(m_pFileEx);
	CsTextFile_Ex *pTextFile_Ex = (CsTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Write(str);
}
