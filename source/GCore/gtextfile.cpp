#include "gtextfile.h"
#include "gtextfile_ex.h"

namespace gsystem { // gsystem

GTextFile::GTextFile(const GString &filename)
: GFile(new detail::GTextFile_Ex(filename))
{

}

GTextFile::GTextFile(detail::GTextFile_Ex *pTextFile_Ex)
: GFile(pTextFile_Ex)
{

}

gbool GTextFile::Read(gsize size, GString &content)
{
	GASSERT(m_pFileEx);
	detail::GTextFile_Ex *pTextFile_Ex = (detail::GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Read(size, content);
}

gbool GTextFile::ReadAll(GString &content)
{
	GASSERT(m_pFileEx);
	detail::GTextFile_Ex *pTextFile_Ex = (detail::GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->ReadAll(content);
}

gbool GTextFile::Write(const GString &content)
{
	GASSERT(m_pFileEx);
	detail::GTextFile_Ex *pTextFile_Ex = (detail::GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Write(content);
}

} // namespace gsystem
