#include "CsBinaryDocument.h"
#include "CsBinaryDocument_Ex.h"

CsBinaryDocument::CsBinaryDocument(const CsString &sFileName)
: CsDocument(new CsBinaryDocument_Ex(sFileName))
{

}

CsBinaryDocument::CsBinaryDocument(CsBinaryDocument_Ex *pBinaryFile_Ex)
: CsDocument(pBinaryFile_Ex)
{

}

cs_bool CsBinaryDocument::Read(cs_size_t size, CsBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsBinaryDocument_Ex *m_pBinaryFile_Ex = (CsBinaryDocument_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Read(size, bytes);
}

cs_bool CsBinaryDocument::ReadAll(CsBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsBinaryDocument_Ex *m_pBinaryFile_Ex = (CsBinaryDocument_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->ReadAll(bytes);
}

cs_bool CsBinaryDocument::Wirte(const CsBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsBinaryDocument_Ex *m_pBinaryFile_Ex = (CsBinaryDocument_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Wirte(bytes);
}
