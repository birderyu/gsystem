#ifndef _CORE_TEXT_FILE_H_
#define _CORE_TEXT_FILE_H_

#include "gfile.h"

class CsTextFile_Ex;

class GAPI GTextFile 
	: public GFile
{
public:
	GTextFile(const GString &sFileName);

	gbool Read(gsize size, GString &);
	gbool ReadAll(GString &);
	gbool Write(const GString &);

protected:
	GTextFile(CsTextFile_Ex *);
};

#endif // _CORE_TEXT_FILE_H_