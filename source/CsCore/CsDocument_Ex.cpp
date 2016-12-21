#include "CsDocument_Ex.h"
#include "CsDocument.h"

CsDocument_Ex::CsDocument_Ex(const CsString &sFileName)
: m_sFileName(sFileName)
, m_pFileStream(NULL)
, m_nOpenMode(CsDocument::NO_OPEN)
{

}

CsDocument_Ex::~CsDocument_Ex()
{
	Close();
}

cs_bool CsDocument_Ex::Valid() const
{
	return m_pFileStream != NULL;
}

CsString CsDocument_Ex::FileName() const
{
	return m_sFileName;
}

cs_void CsDocument_Ex::SetFileName(const CsString &sFileName)
{
	m_sFileName = sFileName;
}

cs_bool CsDocument_Ex::Open(cs_byte nOpenMode)
{
	// 清空缓存区中的数据
	Abort();

	if (m_sFileName.IsEmpty() || 
		m_nOpenMode == CsDocument::NO_OPEN)
	{
		return false;
	}

	errno_t errno;
	cs_cstring open_mode = OpenMode();
	if (!open_mode)
	{
		return false;
	}
	errno = fopen_s(&m_pFileStream, m_sFileName.CString(), open_mode);

	if (!m_pFileStream)
	{
		return false;
	}
	if (errno == 0)
	{
		m_pFileStream = NULL;
		return false;
	}
	return true;
}

cs_void CsDocument_Ex::Close()
{
	if (m_pFileStream)
	{
		Flush();
		fclose(m_pFileStream);
	}
}

cs_bool CsDocument_Ex::CanRead() const
{
	if (m_nOpenMode == CsDocument::NO_OPEN ||
		m_nOpenMode == CsDocument::ONLY_WIRTE)
	{
		return false;
	}
	return true;
}

cs_bool CsDocument_Ex::CanWrite() const
{
	if (m_nOpenMode == CsDocument::NO_OPEN ||
		m_nOpenMode == CsDocument::ONLY_READ)
	{
		return false;
	}
	return true;
}
