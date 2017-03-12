#include "gtextfile.h"
#include "gtextfile_ex.h"

namespace gnova { // gnova

GTextFile::GTextFile(const GString &filename)
: GFile(new extra::GTextFile_Ex(filename))
{

}

GTextFile::GTextFile(extra::GTextFile_Ex *pTextFile_Ex)
: GFile(pTextFile_Ex)
{

}

gbool GTextFile::Read(gsize size, GString &content)
{
	GASSERT(m_pFileEx);
	extra::GTextFile_Ex *pTextFile_Ex = (extra::GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Read(size, content);
}

gbool GTextFile::ReadAll(GString &content)
{
	GASSERT(m_pFileEx);
	extra::GTextFile_Ex *pTextFile_Ex = (extra::GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->ReadAll(content);
}

gbool GTextFile::Write(const GString &content)
{
	GASSERT(m_pFileEx);
	extra::GTextFile_Ex *pTextFile_Ex = (extra::GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Write(content);
}

}