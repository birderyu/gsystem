#include "CsTextFile.h"
#include "CsTextFile_Ex.h"

CsTextFile::CsTextFile(const CsString &sFileName)
: CsFile(new CsTextFile_Ex(sFileName))
{

}

CsTextFile::CsTextFile(CsTextFile_Ex *pTextFile_Ex)
: CsFile(pTextFile_Ex)
{

}

cs_bool CsTextFile::Read(cs_size_t size, CsString &str)
{
	CS_ASSERT(m_pFileEx);
	CsTextFile_Ex *pTextFile_Ex = (CsTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Read(size, str);
}

cs_bool CsTextFile::ReadAll(CsString &str)
{
	CS_ASSERT(m_pFileEx);
	CsTextFile_Ex *pTextFile_Ex = (CsTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->ReadAll(str);
}

cs_bool CsTextFile::Write(const CsString &str)
{
	CS_ASSERT(m_pFileEx);
	CsTextFile_Ex *pTextFile_Ex = (CsTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Write(str);
}
