// 内存文件
#ifndef _CORE_MEMORY_FILE_H_
#define _CORE_MEMORY_FILE_H_

#include "CsFile.h"

class CsMemoryFile
	: public CsFile
{
public:
	CsMemoryFile();

private:
	// 二进制字节流
	//CsBytes m_tBytes;
};

#endif // _CORE_MEMORY_FILE_H_