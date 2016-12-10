#ifndef _CORE_TEXT_FILE_PRIVATE_H_
#define _CORE_TEXT_FILE_PRIVATE_H_

#include "CsFile_Ex.h"

class CsString;

#define LINEBUFSIZE    4096
#define bufsize        32000
#define itemsize       1

#define CS_CR    0x0d
#define CS_LF    0x0a
#define CS_CRLF  0x0d0a
#define CS_LFCR  0x0a0d

class CsTextFile_Ex :public CsFile_Ex
{
public:
	CsTextFile_Ex(const CsString &sFileName);
	cs_bool Open(CsFile::CS_FILE_OPEN_MODE emOpenMode);
	cs_bool ReadLine(CsString &line);
	cs_bool WriteLine(const CsString &line, cs_int format = CS_CRLF);

private:
	cs_ulong bufindex;
	cs_ulong maxbuf;
	cs_ulong filebufsize;
	cs_uchar buf[LINEBUFSIZE];
};

#endif