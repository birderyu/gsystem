// нд╪Ч
#ifndef _CORE_FILE_H_
#define _CORE_FILE_H_

#include "CsObject.h"

class CsFile_Ex;

class CS_API CsFile 
{
public:
	CsFile(CsFile_Ex *);
	virtual ~CsFile();

	virtual cs_bool Valid() const;

	//virtual cs_bool Seek();
	//virtual cs_void Rewind();

protected:
	CsFile_Ex *m_pFileEx;
};

#endif // _FILE_FILE_H_