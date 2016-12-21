#ifndef _CORE_DOCUMENT_EX_H_
#define _CORE_DOCUMENT_EX_H_

#include "CsFile_Ex.h"
#include "CsString.h"
#include <stdio.h>

class CsDocument_Ex
	: public CsFile_Ex
{
public:
	CsDocument_Ex(const CsString &sFileName);
	virtual ~CsDocument_Ex();

	cs_bool Valid() const;
	CsString FileName() const;
	cs_void SetFileName(const CsString &);

	cs_bool Open(cs_byte nOpenMode);
	virtual cs_void Flush() = 0;
	virtual cs_void Abort() = 0;
	cs_void Close();

	cs_bool CanRead() const;
	cs_bool CanWrite() const;

protected:
	virtual cs_cstring OpenMode() const = 0;

protected:
	CsString m_sFileName;
	FILE *m_pFileStream;
	cs_byte m_nOpenMode;
};

#endif // _CORE_DOCUMENT_EX_H_