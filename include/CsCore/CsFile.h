#ifndef _CORE_FILE_H_
#define _CORE_FILE_H_

#include "CsObject.h"
class CsFile_Ex;

class CS_API CsFile 
	: public CsObject
{
public:
	enum CS_FILE_OPEN_MODE
	{
		FILE_OPEN_MODE_NO_OPEN		= 0x0000,
		FILE_OPEN_MODE_ONLY_READ	= 0x0001,
		FILE_OPEN_MODE_ONLY_WIRTE	= 0x0002,
		FILE_OPEN_MODE_READ_WIRTE	= FILE_OPEN_MODE_ONLY_READ | FILE_OPEN_MODE_ONLY_WIRTE,
		FILE_OPEN_MODE_APPEND		= 0x0004,
	};

public:
	CsFile(const CsString &sFileName);
	virtual ~CsFile() = 0;
	virtual cs_bool Open(CS_FILE_OPEN_MODE emOpenMode = FILE_OPEN_MODE_ONLY_READ) = 0;

private:
	CsFile_Ex *m_pFile_Ex;
};

#endif // _CORE_FILE_H_