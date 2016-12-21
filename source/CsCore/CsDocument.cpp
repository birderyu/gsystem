#include "CsDocument.h"
#include "CsDocument_Ex.h"

CsDocument::CsDocument(CsDocument_Ex *pPhysicalDocumnet_Ex)
: CsFile(pPhysicalDocumnet_Ex)
{

}

CsDocument::~CsDocument()
{

}

CsString CsDocument::FileName() const
{
	if (!m_pFileEx)
	{
		return "";
	}
	CsDocument_Ex *m_pPhysicalFile_Ex = (CsDocument_Ex*)m_pFileEx;
	return m_pPhysicalFile_Ex->FileName();
}

cs_void CsDocument::SetFileName(const CsString &sFileName)
{
	if (!m_pFileEx)
	{
		return;
	}
	CsDocument_Ex *m_pPhysicalFile_Ex = (CsDocument_Ex*)m_pFileEx;
	return m_pPhysicalFile_Ex->SetFileName(sFileName);
}

cs_bool CsDocument::Open(OPEN_MODE emOpenMode)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsDocument_Ex *m_pPhysicalFile_Ex = (CsDocument_Ex*)m_pFileEx;
	return m_pPhysicalFile_Ex->Open(emOpenMode);
}

cs_void CsDocument::Flush()
{
	if (!m_pFileEx)
	{
		return;
	}
	CsDocument_Ex *m_pPhysicalFile_Ex = (CsDocument_Ex*)m_pFileEx;
	m_pPhysicalFile_Ex->Flush();
}

cs_void CsDocument::Abort()
{
	if (!m_pFileEx)
	{
		return;
	}
	CsDocument_Ex *m_pPhysicalFile_Ex = (CsDocument_Ex*)m_pFileEx;
	m_pPhysicalFile_Ex->Abort();
}

cs_void CsDocument::Close()
{
	if (!m_pFileEx)
	{
		return;
	}
	CsDocument_Ex *m_pPhysicalFile_Ex = (CsDocument_Ex*)m_pFileEx;
	m_pPhysicalFile_Ex->Close();
}
