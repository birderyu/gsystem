#ifndef _CORE_FILE_EX_H_
#define _CORE_FILE_EX_H_

#include "gnew.h"
#include "gstring.h"
#include <stdio.h>

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

class GFile_Ex
	: public GNewT<GFile_Ex>
{
public:
	GFile_Ex(const GString &sFileName);
	virtual ~GFile_Ex();

	gbool Valid() const;
	gbool EndOfFile() const;

	virtual gbyte Format() const = 0;

	const GString &FileName() const;
	GString &FileName();
	gvoid SetFileName(const GString &);

	gbool Open(gbyte nOpenMode);
	gvoid Flush();
	gvoid Close();

	gbool Seek(glong offset, gbyte mode);
	glong Tell() const;
	gvoid Rewind();

protected:
	gbool CanRead() const;
	gbool CanWrite() const;
	virtual gcstring OpenMode() const = 0;

protected:
	GString m_sFileName;
	FILE *m_pFileStream;
	gbyte m_nOpenMode;
};

} // namespace gsystem.detail
} // namespace gsystem

#endif // _CORE_FILE_EX_H_