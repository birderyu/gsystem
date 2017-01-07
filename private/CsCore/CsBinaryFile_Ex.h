#ifndef _CORE_BINARY_FILE_EX_H_
#define _CORE_BINARY_FILE_EX_H_

#include "CsFile_Ex.h"

class GBytes;

class CsBinaryFile_Ex
	: public CsFile_Ex
{
public:
	CsBinaryFile_Ex(const GString &sFileName);
	virtual ~CsBinaryFile_Ex();

	gbyte Format() const;

	gbool GetByte(gbyte &);
	gbool PutByte(gbyte);

	gbool Read(gsize size, GBytes &);
	gbool ReadAll(GBytes &);
	gbool Write(const GBytes &);

protected:
	gcstring OpenMode() const;
};

#endif // _CORE_BINARY_FILE_EX_H_