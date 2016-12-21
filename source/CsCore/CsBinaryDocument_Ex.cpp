#include "CsBinaryDocument_Ex.h"
#include "CsDocument.h"

#define CS_BINARY_DOCUMNET_BUFFER_SIZE 4096

CsBinaryDocument_Ex::CsBinaryDocument_Ex(const CsString &sFileName)
: CsDocument_Ex(sFileName)
{

}

CsBinaryDocument_Ex::~CsBinaryDocument_Ex()
{

}

cs_void CsBinaryDocument_Ex::Flush()
{
	if (!CanWrite() || m_tBuffer.IsEmpty())
	{
		return;
	}

}

cs_void CsBinaryDocument_Ex::Abort()
{
	m_tBuffer.Clear();
}

cs_bool CsBinaryDocument_Ex::Read(cs_size_t size, CsBytes &bytes)
{
	if (!Valid() || !CanRead() || size <= 0)
	{
		return false;
	}
	cs_size_t bytes_old_size = bytes.Size();
	cs_size_t bytes_new_size = bytes_old_size + size;
	if (bytes_new_size > bytes.Capacity())
	{
		bytes.Reserve(bytes_new_size);
	}

	if (fread(bytes.Tail(), sizeof(cs_byte), size, m_pFileStream) == 0)
	{
		return false;
	}
	bytes.m_nTailCursor += size;
	return true;
}

cs_bool CsBinaryDocument_Ex::ReadAll(CsBytes &bytes)
{
	if (!Valid() || !CanRead())
	{
		return false;
	}
	// TODO
	return false;
}

cs_bool CsBinaryDocument_Ex::Wirte(const CsBytes &bytes)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}
	// TODO
	return false;
}

cs_cstring CsBinaryDocument_Ex::OpenMode() const
{
	switch(m_nOpenMode)
	{
		case CsDocument::NO_OPEN:
			return NULL;
		case CsDocument::ONLY_READ:
			return "rb";
		case CsDocument::ONLY_WIRTE:
			return "wb";
		case CsDocument::READ_WIRTE:
			return "rb+";
		case CsDocument::APPEND:
			return "ab";
		default:
			break;
	}
	return NULL;
}

#undef CS_BINARY_DOCUMNET_BUFFER_SIZE
