#include "CsFileStream.h"

CsFileStream::CsFileStream(CsFile &file)
: m_rFile(file)
{

}

CsFileStream::~CsFileStream()
{

}

cs_bool CsFileStream::HasFile() const
{
	return true;
}
