#ifndef _CORE_TEXT_DOCUMENT_EX_H_
#define _CORE_TEXT_DOCUMENT_EX_H_

#include "gfile_ex.h"

#define G_CR    0x0d
#define G_LF    0x0a
#define G_CRLF  0x0d0a
#define G_LFCR  0x0a0d

class GTextFile_Ex 
	: public GFile_Ex
{
public:
	GTextFile_Ex(const GString &sFileName);

	gbyte Format() const;

	gbool GetChar(guchar &);
	gbool PutChar(guchar);

	gbool Read(gsize size, GString &);
	gbool ReadAll(GString &);
	gbool Write(const GString &);

protected:
	gcstring OpenMode() const;
};

#endif // _CORE_TEXT_DOCUMENT_EX_H_