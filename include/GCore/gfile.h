#ifndef _CORE_FILE_H_
#define _CORE_FILE_H_

#include "gglobal.h"

class GString;
class GFile_Ex;

class GAPI GFile
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
	GFile(GFile_Ex *);
	virtual ~GFile() = 0;

	FILE_FORMAT Format() const;

	gbool Valid() const;
	gbool EndOfFile() const;	

	const GString &FileName() const;
	GString &FileName();
	gvoid SetFileName(const GString &);

	gbool Open(OPEN_MODE);
	gvoid Close();

	gbool Seek(glong offset, SEEK_MODE);
	glong Tell() const; // 负值则表示获取位置失败
	gvoid Rewind();

	// 获取文件的大小，单位，字节
	gsize Size() const;

protected:
	GFile_Ex *m_pFileEx;
};

#endif _CORE_FILE_H_