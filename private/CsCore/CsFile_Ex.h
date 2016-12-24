#ifndef _CORE_FILE_EX_H_
#define _CORE_FILE_EX_H_

#include "CsString.h"
#include <stdio.h>

class CsFile_Ex
	: public CsNewT<CsFile_Ex>
{
public:
	CsFile_Ex(const CsString &sFileName);
	virtual ~CsFile_Ex();

	cs_bool Valid() const;
	cs_bool EndOfFile() const;

	virtual cs_byte Format() const = 0;

	const CsString &FileName() const;
	CsString &FileName();
	cs_void SetFileName(const CsString &);

	cs_bool Open(cs_byte nOpenMode);
	cs_void Flush();
	cs_void Close();

	cs_bool Seek(cs_long offset, cs_byte mode);
	cs_long Tell() const;
	cs_void Rewind();

protected:
	cs_bool CanRead() const;
	cs_bool CanWrite() const;
	virtual cs_cstring OpenMode() const = 0;

protected:
	CsString m_sFileName;
	FILE *m_pFileStream;
	cs_byte m_nOpenMode;
};

#endif // _CORE_FILE_EX_H_