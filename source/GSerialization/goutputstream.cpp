#include "goutputstream.h"

GOutputStream::~GOutputStream()
{

}

gbool GOutputStream::IsOutput() const
{
	return true;
}
