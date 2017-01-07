#include "gfilestream.h"

GFileStream::GFileStream(GFile &file)
: m_rFile(file)
{

}

GFileStream::~GFileStream()
{

}

gbool GFileStream::HasFile() const
{
	return true;
}
