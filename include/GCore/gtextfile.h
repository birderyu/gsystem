#ifndef _CORE_TEXT_FILE_H_
#define _CORE_TEXT_FILE_H_

#include "gfile.h"

class GTextFile_Ex;

class GAPI GTextFile 
	: public GFile
{
public:
	GTextFile(const GString &filename);

	gbool Read(gsize size, GString &content);
	gbool ReadAll(GString &content);
	gbool Write(const GString &content);

protected:
	GTextFile(GTextFile_Ex *);
};

#endif // _CORE_TEXT_FILE_H_