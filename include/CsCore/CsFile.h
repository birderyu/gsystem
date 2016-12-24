#ifndef _CORE_FILE_H_
#define _CORE_FILE_H_

#include "CsGlobal.h"

class CsString;
class CsFile_Ex;

class CS_API CsFile
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

	enum FILE_FORMAT
	{
		BINARY_FILE,
		TEXT_FILE
	};

	enum SEEK_MODE
	{
		SEEK_MODE_START		= 0,
		SEEK_MODE_CURRENT	= 1,
		SEEK_MODE_END		= 2,
	};

public:
	CsFile(CsFile_Ex *);
	virtual ~CsFile() = 0;

	FILE_FORMAT Format() const;

	cs_bool Valid() const;
	cs_bool EndOfFile() const;	

	const CsString &FileName() const;
	CsString &FileName();
	cs_void SetFileName(const CsString &);

	cs_bool Open(OPEN_MODE);
	cs_void Close();

	cs_bool Seek(cs_long offset, SEEK_MODE);
	cs_long Tell() const; // 负值则表示获取位置失败
	cs_void Rewind();

protected:
	CsFile_Ex *m_pFileEx;
};

#endif _CORE_FILE_H_