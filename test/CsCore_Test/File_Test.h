#include "CsString.h"
#include "CsBytes.h"
#include "CsTextFile.h"
#include "CsBinaryFile.h"

cs_void TestTextFile()
{
	CsString sFileName("C:\\Users\\birde\\Desktop\\write.png");

	CsBinaryFile tFile(sFileName);
	tFile.Open(CsFile::ONLY_READ);

	CsBytes bytes;
	tFile.ReadAll(bytes);

	CsString sFileName2("C:\\Users\\birde\\Desktop\\write_copy.png");
	CsBinaryFile tFile2(sFileName2);
	tFile2.Open(CsFile::ONLY_WIRTE);
	tFile2.Write(bytes);

	tFile.Close();
	tFile2.Close();


	cs_int stop = 1;
	stop++;
}