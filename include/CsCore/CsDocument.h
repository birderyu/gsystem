// ÎÄµµ
#ifndef _CORE_DOCUMENT_H_
#define _CORE_DOCUMENT_H_

#include "CsFile.h"
#include "CsString.h"

class CsDocument_Ex;

class CS_API CsDocument
	: public CsFile
{
public:
	enum OPEN_MODE
	{
		NO_OPEN = 0x0000,
		ONLY_READ = 0x0001,
		ONLY_WIRTE = 0x0002,
		READ_WIRTE = ONLY_READ | ONLY_WIRTE,
		APPEND = 0x0004,
	};

public:
	virtual ~CsDocument() = 0;

	CsString FileName() const;
	cs_void SetFileName(const CsString &);

	cs_bool Open(OPEN_MODE emOpenMode);
	virtual cs_void Flush();
	virtual cs_void Abort();
	cs_void Close();

protected:
	CsDocument(CsDocument_Ex *);
};

#endif _CORE_DOCUMENT_H_