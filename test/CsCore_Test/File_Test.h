#include "CsString.h"
#include "CsBytes.h"
#include "CsTextFile.h"
#include "CsBinaryFile.h"

cs_void TestTextFile()
{
	CsString sFileName("C:\\Users\\birde\\Desktop\\新建文本文档 (2).txt");

	CsTextFile tFile(sFileName);
	tFile.Open(CsFile::ONLY_READ);

	CsString str;
	tFile.ReadAll(str);

	tFile.Close();

	cs_size_t s = str.Size();
	cs_cstring cs = str.CString();

	cs_int stop = 1;
	stop++;
}