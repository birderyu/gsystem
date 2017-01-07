#include "gstring.h"
#include "gbytes.h"
#include "gtextfile.h"
#include "gbinaryfile.h"

gvoid TestTextFile()
{
	GString sFileName("C:\\Users\\birde\\Desktop\\write.png");

	GBinaryFile tFile(sFileName);
	tFile.Open(GFile::ONLY_READ);

	GBytes bytes;
	tFile.ReadAll(bytes);

	GString sFileName2("C:\\Users\\birde\\Desktop\\write_copy.png");
	GBinaryFile tFile2(sFileName2);
	tFile2.Open(GFile::ONLY_WIRTE);
	tFile2.Write(bytes);

	tFile.Close();
	tFile2.Close();


	gint stop = 1;
	stop++;
}