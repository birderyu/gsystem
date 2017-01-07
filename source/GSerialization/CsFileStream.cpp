#include "CsFileStream.h"

CsFileStream::CsFileStream(GFile &file)
: m_rFile(file)
{

}

CsFileStream::~CsFileStream()
{

}

gbool CsFileStream::HasFile() const
{
	return true;
}
